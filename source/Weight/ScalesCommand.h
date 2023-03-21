#pragma once

#include "ScalesInterface.h"
#include "TerminalInterface.h"
#include "TerminalCallbackInterface.h"
#include "ScalesTerminalCommands.h"

namespace coffeescales::weight
{

class ScalesCommand final : public terminal::TerminalCallbackInterface
{
public:
    ScalesCommand(ScalesInterface &scales, terminal::TerminalInterface &terminal);

    // TerminalCallbackInterface
    bool TerminalCommand(terminal::CommandArgs &args) override;

    [[nodiscard]] const char *CommandName() const override
    { return ScalesTerminalCommands::CommandName; }

private:
    ScalesInterface &mScales;
    terminal::TerminalInterface &mTerminal;
};

}
