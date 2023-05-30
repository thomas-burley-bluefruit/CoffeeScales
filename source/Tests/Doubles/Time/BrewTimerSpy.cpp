#include "BrewTimerSpy.h"

namespace coffeescales::time
{

void BrewTimerSpy::Start()
{
    StartCalled = true;
}

void BrewTimerSpy::Reset() {}

bool BrewTimerSpy::RegisterCallback(TimerIncrementCallbackInterface* callback)
{
    RegisterCallbackCalled = true;
    RegisteredCallback = callback;
    return true;
}

}