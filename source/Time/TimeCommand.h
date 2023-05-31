#pragma once

#include "TerminalCallbackInterface.h"
#include "TerminalInterface.h"
#include "TimerAutoStartInterface.h"
#include "TimeTerminalCommands.h"

namespace coffeescales::time
{

class TimeCommand final : public terminal::TerminalCallbackInterface
{
  public:
    TimeCommand(TimerAutoStartInterface& timerAutoStart, terminal::TerminalInterface& terminal);

    // TerminalCallbackInterface
    bool TerminalCommand(terminal::CommandArgs& args) override;

    [[nodiscard]] const char* CommandName() const override
    {
        return TimeTerminalCommands::CommandName;
    }

  private:
    TimerAutoStartInterface& mTimerAutoStart;
    terminal::TerminalInterface& mTerminal;
};

}
