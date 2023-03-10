#pragma once

#include "TerminalCallbackInterface.h"

#include <cstddef>

namespace terminal
{

class TerminalInterface
{
public:
    ~TerminalInterface() = default;
    virtual void TextOut(const char *text) const = 0;
    virtual bool RegisterCommandHandler(TerminalCallbackInterface* callback) = 0;
};

}