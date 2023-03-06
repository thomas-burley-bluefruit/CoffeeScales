#pragma once

#include "HalInit.h"
#include "HX711Driver.h"
#include "System.h"
#include "Terminal.h"
#include "Uart.h"

class Instantiation
{
public:
    Instantiation();
    void Init();
    const terminal::Terminal& Terminal() const;
    halwrapper::System& System();
    drivers::HX711Driver& Hx711();

private:
    halwrapper::HalInit mHalInit;
    halwrapper::System mSystem;
    halwrapper::Uart mUart;
    terminal::Terminal mTerminal;
    drivers::HX711Driver mHx711;
};
