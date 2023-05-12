#include "Instantiation.h"
#include "gfx.h"
#include "DisplayGpio.h"

using namespace ::coffeescales;
using namespace ::drivers;
using namespace ::halwrapper;
using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart), mHx711(mSystem),
                                 mEeprom(mSpi),
                                 mScalesMemoryItem(mEeprom),
                                 mScales(mHx711, mSystem, mTerminal, mScalesMemoryItem),
                                 mScalesCommand(mScales, mTerminal),
                                 mWeightDisplayItem(mUgfxWrapper, mScales, mTerminal),
                                 mDisplayCommand(mTerminal, mWeightDisplayItem),
                                 mTareButton(buttons::Button::Tare, mTareButtonGpio, mSystem)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mSystem.Init();
    mSpi.Init();
    mTerminal.Start();
    mScalesMemoryItem.Init();
    mScales.Init();
    DisplayGpio_Init();
    gfxInit();
    mWeightDisplayItem.Init();
    mTareButtonGpio.Init();
    mTareButton.Init();
}

System &Instantiation::System()
{
    return mSystem;
}

Terminal &Instantiation::Terminal()
{
    return mTerminal;
}

weight::Scales &Instantiation::Scales()
{
    return mScales;
}

drivers::HX711Driver &Instantiation::Hx711()
{
    return mHx711;
}

display::UgfxWrapper &Instantiation::UgfxWrapper()
{
    return mUgfxWrapper;
}