#include "Instantiation.h"

using namespace ::drivers;
using namespace ::halwrapper;
using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart), mHx711(mSystem)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mUart.Init();
    mSystem.Init();
}

System &Instantiation::System()
{
    return mSystem;
}

const Terminal& Instantiation::Terminal() const
{
    return mTerminal;
}

drivers::HX711Driver &Instantiation::Hx711()
{
    return mHx711;
}