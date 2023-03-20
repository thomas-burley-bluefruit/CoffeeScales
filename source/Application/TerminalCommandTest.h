#pragma once

#include "TerminalInterface.h"
#include "TerminalCallbackInterface.h"

namespace coffeescales::terminal
{

class TerminalCommandTest final : public TerminalCallbackInterface
{
public:
    explicit TerminalCommandTest(TerminalInterface& terminal);
    bool TerminalCommand(CommandArgs &args) override;
    [[nodiscard]] const char *CommandName() const override;

private:
    TerminalInterface& mTerminal;
};

}
