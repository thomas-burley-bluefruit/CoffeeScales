#include "gtest/gtest.h"

#include "GenericTerminalCommands.h"
#include "TerminalSpy.h"
#include "TimeCommand.h"
#include "TimerAutoStartSpy.h"

#include <string>
#include <vector>

using namespace ::coffeescales::terminal;
using namespace ::coffeescales::time;

class TimeCommandTests : public testing::Test
{
  public:
    TimeCommandTests() :
        mTimeCommand(mTimerAutoStart, mTerminal)
    {
    }

    TerminalSpy mTerminal;
    TimerAutoStartSpy mTimerAutoStart;
    TimeCommand mTimeCommand;
};

TEST_F(TimeCommandTests, callback_is_registered_with_terminal)
{
    ASSERT_TRUE(mTerminal.RegisterCommandHandlerCalled);
    ASSERT_EQ(mTerminal.TerminalCallback, &mTimeCommand);
}

TEST_F(TimeCommandTests,
       auto_command_enabled_timer_auto_start)
{
    // Given
    CommandArgs args;
    args.SetCommandArg(0, TimeTerminalCommands::Auto);
    args.Count++;

    // When
    ASSERT_TRUE(mTimeCommand.TerminalCommand(args));

    // Then
    ASSERT_TRUE(mTimerAutoStart.EnableCalled);
}

TEST_F(TimeCommandTests,
       unrecognised_command_rejected)
{
    // Given
    CommandArgs args;
    args.SetCommandArg(0, "blah");
    args.Count++;

    // When
    ASSERT_FALSE(mTimeCommand.TerminalCommand(args));

    // Then
    ASSERT_FALSE(mTimerAutoStart.EnableCalled);
}
