#include "Instantiation.h"

using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart), mHX711(mTerminal)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mDelay.Init();
    mUart.Init();
}

halwrapper::Delay &Instantiation::Delay()
{
    return mDelay;
}

const Terminal& Instantiation::Terminal() const
{
    return mTerminal;
}