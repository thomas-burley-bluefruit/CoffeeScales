#include "BrewTimerSpy.h"

namespace coffeescales::time
{

void BrewTimerSpy::Start()
{
    StartCalled = true;
}

void BrewTimerSpy::Reset()
{
    ResetCalled = true;
}

bool BrewTimerSpy::RegisterCallback(TimerIncrementCallbackInterface* callback)
{
    RegisterCallbackCalled = true;
    RegisteredCallback = callback;
    return true;
}

}