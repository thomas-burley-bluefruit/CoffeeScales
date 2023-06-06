#pragma once

#include "BrewTimer.h"
#include "ButtonDriver.h"
#include "ButtonGpio.h"
#include "DisplayCommand.h"
#include "DisplayManager.h"
#include "EepromDriver.h"
#include "HalInit.h"
#include "HX711Driver.h"
#include "InterruptTimerGpio.h"
#include "PourRate.h"
#include "Scales.h"
#include "ScalesCommand.h"
#include "ScalesMemoryItem.h"
#include "Spi.h"
#include "System.h"
#include "Terminal.h"
#include "Time.h"
#include "TimeCommand.h"
#include "TimeDisplayItem.h"
#include "TimerAutoStart.h"
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
    terminal::Terminal& Terminal();
    weight::Scales& Scales();
    time::BrewTimer& BrewTimer();
    display::DisplayManager& DisplayManager();

  private:
    halwrapper::HalInit mHalInit;
    halwrapper::System mSystem;
    halwrapper::Time mTime;
    halwrapper::Uart mUart;
    terminal::Terminal mTerminal;
    drivers::HX711Driver mHx711;
    halwrapper::Spi mSpi;
    drivers::EepromDriver mEeprom;
    weight::ScalesMemoryItem mScalesMemoryItem;
    halwrapper::InterruptTimerGpio mInterruptTimerGpio;
    halwrapper::ButtonGpio mTareButtonGpio;
    drivers::ButtonDriver mTareButton;
    weight::Scales mScales;
    weight::ScalesCommand mScalesCommand;
    weight::PourRate mPourRate;
    halwrapper::ButtonGpio mTimerButtonGpio;
    drivers::ButtonDriver mTimerButton;
    time::BrewTimer mBrewTimer;
    time::TimerAutoStart mTimerAutoStart;
    time::TimeCommand mTimeCommand;
    display::UgfxWrapper mUgfxWrapper;
    display::DisplayManager mDisplayManager;
    display::TimeDisplayItem mTimeDisplayItem;
    display::WeightDisplayItem mWeightDisplayItem;
    display::DisplayCommand mDisplayCommand;
};

}
