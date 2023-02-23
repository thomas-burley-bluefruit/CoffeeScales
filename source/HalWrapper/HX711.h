#pragma once
#include "TerminalInterface.h"

namespace halwrapper
{

class HX711
{
public:
    HX711(const terminal::TerminalInterface& terminal);
    ~HX711() = default;

private:
    const terminal::TerminalInterface& mTerminal;
};

}