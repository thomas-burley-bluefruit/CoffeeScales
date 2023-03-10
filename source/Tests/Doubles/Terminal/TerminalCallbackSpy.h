#pragma once

#include "TerminalCallbackInterface.h"

namespace terminal
{

class TerminalCallbackSpy : public TerminalCallbackInterface
{
public:
    bool Callback(CommandArgs &args) override;
    const char *CommandName() const override;

    CommandArgs CallbackArgs;
    size_t CallbackCount = 0;
    const char* CommandNameValue = "commandspy";
};

}
