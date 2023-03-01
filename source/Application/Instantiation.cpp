#include "Instantiation.h"

using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mUart.Init();
    mDelay.Init();
    mHX711.Init();
}

halwrapper::Delay &Instantiation::Delay()
{
    return mDelay;
}

const Terminal& Instantiation::Terminal() const
{
    return mTerminal;
}