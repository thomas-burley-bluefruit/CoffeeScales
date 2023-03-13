#pragma once

#include "TerminalInterface.h"
#include "TerminalCallbackInterface.h"

namespace coffeescales::terminal
{

class TerminalCommandTest final : public TerminalCallbackInterface
{
public:
    TerminalCommandTest(TerminalInterface& terminal);
    bool Callback(CommandArgs &args) override;
    const char *CommandName() const override;

private:
    TerminalInterface& mTerminal;
};

}
