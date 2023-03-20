#pragma once

#include "TerminalCallbackInterface.h"

namespace coffeescales::terminal
{

class TerminalCallbackSpy : public TerminalCallbackInterface
{
public:
    bool TerminalCommand(CommandArgs &args) override;
    [[nodiscard]] const char *CommandName() const override;

    CommandArgs CallbackArgs;
    size_t CallbackCount = 0;
    const char *CommandNameValue = "commandspy";
};

}
