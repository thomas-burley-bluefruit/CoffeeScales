#pragma once

#include "HalInit.h"
#include "HX711.h"
#include "Terminal.h"
#include "Uart.h"

class Instantiation
{
public:
    Instantiation();
    void Init();
    const terminal::Terminal& Terminal() const;

private:
    halwrapper::HalInit mHalInit;
    halwrapper::Uart mUart;
    terminal::Terminal mTerminal;
    halwrapper::HX711 mHX711;
};
