#include "gtest/gtest.h"

#include "DisplayCommand.h"
#include "DisplayItemSpy.h"
#include "DisplaySpy.h"
#include "GenericTerminalCommands.h"
#include "ScalesSpy.h"
#include "TerminalSpy.h"

#include <string>

using namespace ::coffeescales;

class DisplayCommandTests : public testing::Test
{
public:
    DisplayCommandTests() : mCommand(mTerminal, mWeightDisplayItem)
    {}

    terminal::TerminalSpy mTerminal;
    display::DisplayItemSpy mWeightDisplayItem;
    display::DisplayCommand mCommand;
};

TEST_F(DisplayCommandTests, callback_is_registered_with_terminal)
{
    ASSERT_TRUE(mTerminal.RegisterCommandHandlerCalled);
    ASSERT_EQ(mTerminal.TerminalCallback, &mCommand);
}

TEST_F(DisplayCommandTests,
       weight_on_command_turns_weight_display_item_debug_on)
{
    // Given
    terminal::CommandArgs args;
    args.SetCommandArg(0, display::DisplayTerminalCommands::Weight);
    args.Count++;
    args.SetCommandArg(1, terminal::GenericTerminalCommands::On);
    args.Count++;

    // When
    mCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mWeightDisplayItem.DebugPrintCalled);
    ASSERT_TRUE(mWeightDisplayItem.DebugPrintValue);
}

TEST_F(DisplayCommandTests,
       weight_off_command_turns_weight_display_item_debug_off)
{
    // Given
    terminal::CommandArgs args;
    args.SetCommandArg(0, display::DisplayTerminalCommands::Weight);
    args.Count++;
    args.SetCommandArg(1, terminal::GenericTerminalCommands::Off);
    args.Count++;

    // When
    mCommand.TerminalCommand(args);

    // Then
    ASSERT_TRUE(mWeightDisplayItem.DebugPrintCalled);
    ASSERT_FALSE(mWeightDisplayItem.DebugPrintValue);
}