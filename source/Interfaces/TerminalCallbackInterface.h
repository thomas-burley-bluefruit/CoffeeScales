#pragma once

#include "CommandArgs.h"

namespace terminal
{

class TerminalCallbackInterface
{
public:
    ~TerminalCallbackInterface() = default;
    virtual bool Callback(CommandArgs& args) = 0;
    virtual const char* CommandName() const = 0;
    static constexpr size_t MaxCommandNameLength = 32;
};

}