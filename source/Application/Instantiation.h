#pragma once

#include "HalInit.h"
#include "HX711Driver.h"
#include "Scales.h"
#include "ScalesCommand.h"
#include "System.h"
#include "Terminal.h"
#include "Uart.h"
#include "TerminalCommandTest.h"

namespace coffeescales
{

class Instantiation
{
public:
    Instantiation();
    void Init();
    terminal::Terminal &Terminal();
    halwrapper::System &System();
    drivers::HX711Driver &Hx711();
    weight::Scales &Scales();

private:
    halwrapper::HalInit mHalInit;
    halwrapper::System mSystem;
    halwrapper::Uart mUart;
    terminal::Terminal mTerminal;
    drivers::HX711Driver mHx711;
    weight::Scales mScales;
    weight::ScalesCommand mScalesCommand;
};

}
