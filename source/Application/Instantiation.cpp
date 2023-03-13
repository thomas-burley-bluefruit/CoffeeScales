#include "Instantiation.h"

using namespace ::coffeescales;
using namespace ::drivers;
using namespace ::halwrapper;
using namespace ::terminal;

Instantiation::Instantiation() : mTerminal(mUart), mHx711(mSystem), mTerminalCommandTest(mTerminal)
{
}

void Instantiation::Init()
{
    mHalInit.Init();
    mSystem.Init();
    mTerminal.Start();
}

System &Instantiation::System()
{
    return mSystem;
}

Terminal& Instantiation::Terminal()
{
    return mTerminal;
}

drivers::HX711Driver &Instantiation::Hx711()
{
    return mHx711;
}