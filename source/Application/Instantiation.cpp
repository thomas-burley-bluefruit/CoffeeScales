#include "Instantiation.h"

using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart)
{
}

void Instantiation::Init()
{
    mUart.Init();
}

const Terminal& Instantiation::Terminal() const
{
    return mTerminal;
}