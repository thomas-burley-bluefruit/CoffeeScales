#pragma once

#include <cstddef>

namespace terminal
{

class TerminalInterface
{
public:
    ~TerminalInterface() = default;
    virtual void TextOut(const char *text) const = 0;
};

}