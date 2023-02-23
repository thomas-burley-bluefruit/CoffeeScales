#pragma once

#include "Terminal.h"
#include "Uart.h"

class Instantiation
{
public:
    Instantiation();
    void Init();
    const terminal::Terminal& Terminal() const;

private:
    halwrapper::Uart mUart;
    terminal::Terminal mTerminal;
};
