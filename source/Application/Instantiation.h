#pragma once

#include "DisplayCommand.h"
#include "EepromDriver.h"
#include "HalInit.h"
#include "HX711Driver.h"
#include "Scales.h"
#include "ScalesCommand.h"
#include "ScalesMemoryItem.h"
#include "Spi.h"
#include "System.h"
#include "ButtonDriver.h"
#include "TareButtonGpio.h"
#include "Terminal.h"
#include "Uart.h"
#include "UgfxWrapper.h"
#include "WeightDisplayItem.h"

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
    display::UgfxWrapper &UgfxWrapper();

private:
    halwrapper::HalInit mHalInit;
    halwrapper::System mSystem;
    halwrapper::Uart mUart;
    terminal::Terminal mTerminal;
    drivers::HX711Driver mHx711;
    halwrapper::Spi mSpi;
    drivers::EepromDriver mEeprom;
    weight::ScalesMemoryItem mScalesMemoryItem;
    weight::Scales mScales;
    weight::ScalesCommand mScalesCommand;
    display::UgfxWrapper mUgfxWrapper;
    display::WeightDisplayItem mWeightDisplayItem;
    display::DisplayCommand mDisplayCommand;
    halwrapper::TareButtonGpio mTareButtonGpio;
    drivers::ButtonDriver mTareButton;
};

}
