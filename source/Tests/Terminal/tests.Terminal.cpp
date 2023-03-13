#include "gtest/gtest.h"
#include "Terminal.h"
#include "TerminalCallbackSpy.h"
#include "UartSpy.h"

#include <string>

using namespace ::coffeescales::halwrapper;
using namespace ::coffeescales::terminal;
using ::std::string;

class TerminalTests : public testing::Test
{
public:
    TerminalTests() : mTerminal(mUart) {}

protected:
    void SendCommand(string command)
    {
        for (auto ch : command)
            mTerminal.OnReceiveInterrupt(static_cast<uint8_t>(ch));
    }

    UartSpy mUart;
    Terminal mTerminal;
    TerminalCallbackSpy mTerminalCallback;
};

TEST_F(TerminalTests, Start_inits_uart)
{
    // Given, when
    mTerminal.Start();

    // Then
    ASSERT_TRUE(mUart.InitCalled);
}

TEST_F(TerminalTests, Start_sets_uart_callback)
{
    // Given, when
    mTerminal.Start();

    // Then
    ASSERT_TRUE(mUart.SetCallbackCalled);
    ASSERT_EQ(&mTerminal, mUart.Callback);
}

TEST_F(TerminalTests, TextOut_passes_correct_data_to_uart)
{
    // Given
    const char* text = "Hello world\n";

    // When
    mTerminal.TextOut(text);

    // Then
    ASSERT_TRUE(mUart.TransmitCalled);
    ASSERT_EQ(mUart.TxSize, strlen(text));
    ASSERT_STREQ(reinterpret_cast<const char*>(mUart.TxData), text);
}

TEST_F(TerminalTests, Can_register_command_handler)
{
    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));
}

TEST_F(TerminalTests, Can_only_register_max_handlers)
{
    for (int i = 0; i < Terminal::MaxCommandHandlers; i++)
        ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    ASSERT_FALSE(mTerminal.RegisterCommandHandler(&mTerminalCallback));
}

TEST_F(TerminalTests, RegisterCommandHandler_fails_for_too_long_command_name)
{
    // Given
    char nameTooLong[TerminalCallbackInterface::MaxCommandNameLength + 2]{};
    memset(nameTooLong, 'A', TerminalCallbackInterface::MaxCommandNameLength + 1);
    mTerminalCallback.CommandNameValue = nameTooLong;

    // When, then
    ASSERT_FALSE(mTerminal.RegisterCommandHandler(&mTerminalCallback));
}

TEST_F(TerminalTests, Task_calls_callback_for_command_after_terminating_character_received)
{
    // Given
    string commandName = "testcommand";
    mTerminalCallback.CommandNameValue = commandName.c_str();

    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    SendCommand(commandName + "\n");
    mTerminal.Task();

    // Then
    ASSERT_EQ(1, mTerminalCallback.CallbackCount);
}

TEST_F(TerminalTests, Commands_are_only_processed_once)
{
    // Given
    string commandName = "testcommand";
    mTerminalCallback.CommandNameValue = commandName.c_str();

    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    SendCommand(commandName + "\n");
    mTerminal.Task();
    ASSERT_EQ(1, mTerminalCallback.CallbackCount);
    mTerminal.Task();

    // Then
    ASSERT_EQ(1, mTerminalCallback.CallbackCount);
}

TEST_F(TerminalTests, Command_arg_is_passed_to_handler)
{
    // Given
    string commandName = "testcommand";
    string arg = "arg0";
    string command = commandName + " " + arg + '\n';

    mTerminalCallback.CommandNameValue = commandName.c_str();
    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    SendCommand(command);
    mTerminal.Task();

    // Then
    ASSERT_EQ(1, mTerminalCallback.CallbackCount);
    ASSERT_TRUE(mTerminalCallback.CallbackArgs.Arg0Is(arg.c_str()));
}

TEST_F(TerminalTests, Multiple_command_args_are_passed_to_handler)
{
    // Given
    string commandName = "testcommand";
    string arg0 = "arg0";
    string arg1 = "arg1";
    string command = commandName + " " + arg0 + " " + arg1 + '\n';

    mTerminalCallback.CommandNameValue = commandName.c_str();
    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    SendCommand(command);
    mTerminal.Task();

    // Then
    ASSERT_EQ(1, mTerminalCallback.CallbackCount);
    ASSERT_TRUE(mTerminalCallback.CallbackArgs.Arg0Is(arg0.c_str()));
    ASSERT_TRUE(mTerminalCallback.CallbackArgs.Arg1Is(arg1.c_str()));
}

TEST_F(TerminalTests, Number_of_args_is_limited)
{
    // Given
    string commandName = "testcommand";
    mTerminalCallback.CommandNameValue = commandName.c_str();

    string arg = "arg";

    string command = commandName + " ";
    for (size_t i = 0; i < CommandArgs::MaxArguments + 1; ++i)
        command += arg + " ";
    command += "\n";

    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    SendCommand(command);
    mTerminal.Task();

    // Then
    ASSERT_EQ(CommandArgs::MaxArguments, mTerminalCallback.CallbackArgs.Count);
}

TEST_F(TerminalTests, Partially_recognised_command_does_not_call_handler)
{
    // Given
    const char* commandName = "testcommand\n";
    mTerminalCallback.CommandNameValue = commandName;

    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    string command = "testco\n";
    SendCommand(command);
    mTerminal.Task();

    // Then
    ASSERT_EQ(0, mTerminalCallback.CallbackCount);
}

TEST_F(TerminalTests, Double_space_between_commands_is_handled)
{
    // Given
    string commandName = "testcommand";
    string arg = "arg0";
    string command = commandName + "  " + arg + '\n';

    mTerminalCallback.CommandNameValue = commandName.c_str();
    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    SendCommand(command);
    mTerminal.Task();

    // Then
    ASSERT_EQ(1, mTerminalCallback.CallbackCount);
    ASSERT_EQ(1, mTerminalCallback.CallbackArgs.Count);
    ASSERT_TRUE(mTerminalCallback.CallbackArgs.Arg0Is(arg.c_str()));
}

TEST_F(TerminalTests, Multiple_extraneous_spaces_between_commands_are_handled)
{
    // Given
    string commandName = "testcommand";
    string arg0 = "arg0";
    string arg1 = "arg1";
    string command = commandName + "     " + arg0 + "      " + arg1 + '\n';

    mTerminalCallback.CommandNameValue = commandName.c_str();
    ASSERT_TRUE(mTerminal.RegisterCommandHandler(&mTerminalCallback));

    // When
    SendCommand(command);
    mTerminal.Task();

    // Then
    ASSERT_EQ(1, mTerminalCallback.CallbackCount);
    ASSERT_EQ(2, mTerminalCallback.CallbackArgs.Count);
    ASSERT_TRUE(mTerminalCallback.CallbackArgs.Arg0Is(arg0.c_str()));
    ASSERT_TRUE(mTerminalCallback.CallbackArgs.Arg1Is(arg1.c_str()));
}