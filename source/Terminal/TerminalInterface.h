#pragma once

#include <cstddef>

namespace terminal
{

class TerminalInterface
{
    ~TerminalInterface() = default;
    virtual void Transmit(const char* txData, size_t size) = 0;
};

}