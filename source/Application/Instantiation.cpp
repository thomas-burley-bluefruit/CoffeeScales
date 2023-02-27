#include "Instantiation.h"

using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart), mHX711(mTerminal)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mUart.Init();
}

const Terminal& Instantiation::Terminal() const
{
    return mTerminal;
}