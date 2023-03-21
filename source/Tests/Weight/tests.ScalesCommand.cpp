#include "gtest/gtest.h"

#include "GenericTerminalCommands.h"
#include "ScalesCommand.h"
#include "ScalesSpy.h"
#include "TerminalSpy.h"

#include <string>
#include <vector>

using namespace ::coffeescales::terminal;
using namespace ::coffeescales::weight;

class ScalesCommandTests : public testing::Test
{
public:
    ScalesCommandTests() : mScalesCommand(mScales, mTerminal)
    {}

    static void SetCommandArg(CommandArgs &args, size_t index, const char *arg)
    {
        if (index > CommandArgs::MaxArguments - 1)
            return;

        strncpy_s(args.Arguments[index].data(), CommandArgs::MaxArgLength,
                  arg, CommandArgs::MaxArgLength);
    }

    TerminalSpy mTerminal;
    ScalesSpy mScales;
    ScalesCommand mScalesCommand;
};

TEST_F(ScalesCommandTests, callback_is_registered_with_terminal)
{
    ASSERT_TRUE(mTerminal.RegisterCommandHandlerCalled);
    ASSERT_EQ(mTerminal.TerminalCallback, &mScalesCommand);
}

TEST_F(ScalesCommandTests,
       calibrate_command_calls_CalibrateInit_on_scales)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Calibrate);
    args.Count++;

    // When
    mScalesCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mScales.CalibrateInitCalled);
}

TEST_F(ScalesCommandTests,
       tare_command_calls_TareInit_on_scales)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Tare);
    args.Count++;

    // When
    mScalesCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mScales.TareInitCalled);
}

TEST_F(ScalesCommandTests,
       calibrate_set_command_calls_CalibrateSet_on_scales)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Calibrate);
    args.Count++;
    SetCommandArg(args, 1, ScalesTerminalCommands::Set);
    args.Count++;

    // When
    mScalesCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mScales.CalibrateSetCalled);
}

TEST_F(ScalesCommandTests,
       adc_on_command_turns_scale_adc_debug_print_on)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Adc);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::On);
    args.Count++;

    // When
    mScalesCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mScales.AdcDebugPrintCalled);
    ASSERT_TRUE(mScales.AdcDebugPrintValue);
}

TEST_F(ScalesCommandTests,
       adc_off_command_turns_scale_adc_debug_print_off)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Adc);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::Off);
    args.Count++;

    // When
    mScalesCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mScales.AdcDebugPrintCalled);
    ASSERT_FALSE(mScales.AdcDebugPrintValue);
}

TEST_F(ScalesCommandTests,
       weight_on_command_turns_scale_weight_debug_print_on)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Weight);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::On);
    args.Count++;

    // When
    mScalesCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mScales.WeightDebugPrintCalled);
    ASSERT_TRUE(mScales.WeightDebugPrintValue);
}

TEST_F(ScalesCommandTests,
       weight_off_command_turns_scale_weight_debug_print_off)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Weight);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::Off);
    args.Count++;

    // When
    mScalesCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mScales.WeightDebugPrintCalled);
    ASSERT_FALSE(mScales.WeightDebugPrintValue);
}
