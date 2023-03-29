#include "Instantiation.h"

using namespace ::coffeescales;
using namespace ::drivers;
using namespace ::halwrapper;
using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart), mHx711(mSystem),
                                 mEeprom(mSpi),
                                 mScalesMemoryItem(mEeprom),
                                 mScales(mHx711, mSystem, mTerminal, mScalesMemoryItem),
                                 mScalesCommand(mScales, mTerminal)
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