#pragma once

#include "HalInit.h"
#include "HX711Driver.h"
#include "System.h"
#include "Terminal.h"
#include "Uart.h"
#include "TerminalCommandTest.h"

class Instantiation
{
public:
    Instantiation();
    void Init();
    terminal::Terminal& Terminal();
    halwrapper::System& System();
    drivers::HX711Driver& Hx711();

private:
    halwrapper::HalInit mHalInit;
    halwrapper::System mSystem;
    halwrapper::Uart mUart;
    terminal::Terminal mTerminal;
    drivers::HX711Driver mHx711;
    terminal::TerminalCommandTest mTerminalCommandTest;
};
