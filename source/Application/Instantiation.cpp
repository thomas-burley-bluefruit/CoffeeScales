#include "Instantiation.h"

using namespace ::coffeescales;
using namespace ::drivers;
using namespace ::halwrapper;
using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart), mHx711(mSystem), mScales(mHx711, mSystem, mTerminal)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mSystem.Init();
    mTerminal.Start();
    mScales.Tare();
}

System &Instantiation::System()
{
    return mSystem;
}

Terminal& Instantiation::Terminal()
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