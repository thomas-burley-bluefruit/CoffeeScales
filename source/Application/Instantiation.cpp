#include "Instantiation.h"
#include "ButtonMapping.h"
#include "DisplayGpio.h"
#include "gfx.h"

using namespace ::coffeescales;
using namespace ::drivers;
using namespace ::halwrapper;
using namespace ::terminal;

Instantiation::Instantiation() :
    mTerminal(mUart),
    mHx711(mSystem),
    mEeprom(mSpi),
    mScalesMemoryItem(mEeprom),
    mTareButtonGpio(TareButtonGpioPort, TareButtonPin),
    mTareButton(buttons::Button::Tare, mTareButtonGpio, mInterruptTimerGpio, mTime),
    mScales(mHx711, mSystem, mTerminal, mScalesMemoryItem, mTareButton),
    mScalesCommand(mScales, mTerminal),
    mTimerButtonGpio(TimerButtonGpioPort, TimerButtonPin),
    mTimerButton(buttons::Button::Timer, mTimerButtonGpio, mInterruptTimerGpio, mTime),
    mBrewTimer(mSystem, mTimerButton),
    mTimerAutoStart(mBrewTimer, mScales, mTimerButton),
    mTimeCommand(mTimerAutoStart, mTerminal),
    mDisplayManager(mUgfxWrapper),
    mTimeDisplayItem(mDisplayManager, mUgfxWrapper, mBrewTimer, mTimerAutoStart),
    mWeightDisplayItem(mDisplayManager, mUgfxWrapper, mScales, mTerminal),
    mDisplayCommand(mTerminal, mWeightDisplayItem)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mSystem.Init();
    mSpi.Init();
    mTerminal.Start();
    mScalesMemoryItem.Init();
    mTareButtonGpio.Init();
    mTareButton.Init();
    mScales.Init();
    mTimerButtonGpio.Init();
    mTimerButton.Init();
    mBrewTimer.Init();
    DisplayGpio_Init();
    gfxInit();
    mDisplayManager.Init();
    mInterruptTimerGpio.Init();
}

Terminal& Instantiation::Terminal()
{
    return mTerminal;
}

weight::Scales& Instantiation::Scales()
{
    return mScales;
}

time::BrewTimer& Instantiation::BrewTimer()
{
    return mBrewTimer;
}

display::DisplayManager& Instantiation::DisplayManager()
{
    return mDisplayManager;
}