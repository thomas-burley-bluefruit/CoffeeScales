#include "TimeCommand.h"

using namespace ::coffeescales;
using namespace ::coffeescales::time;

TimeCommand::TimeCommand(TimerAutoStartInterface& timerAutoStart,
    terminal::TerminalInterface& terminal) :
    mTimerAutoStart(timerAutoStart),
    mTerminal(terminal)
{
    mTerminal.RegisterCommandHandler(this);
}

bool TimeCommand::TerminalCommand(terminal::CommandArgs& args)
{
    if (args.Arg0Is(TimeTerminalCommands::Auto))
    {
        mTimerAutoStart.Enable();
        return true;
    }

    return false;
}
