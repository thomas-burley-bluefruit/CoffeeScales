#include "Instantiation.h"
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
    mTareButton(buttons::Button::Tare, mTareButtonGpio, mSystem),
    mScales(mHx711, mSystem, mTerminal, mScalesMemoryItem, mTareButton),
    mScalesCommand(mScales, mTerminal),
    mBrewTimer(mSystem),
    mDisplayManager(mUgfxWrapper),
    mTimeDisplayItem(mDisplayManager, mUgfxWrapper, mBrewTimer),
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
    DisplayGpio_Init();
    gfxInit();
    mDisplayManager.Init();
}

Terminal& Instantiation::Terminal()
{
    return mTerminal;
}

weight::Scales& Instantiation::Scales()
{
    return mScales;
}

display::DisplayManager& Instantiation::DisplayManager()
{
    return mDisplayManager;
}