#include "TimerAutoStartSpy.h"

using namespace ::coffeescales::time;

void TimerAutoStartSpy::Enable()
{
    EnableCalled = true;
}

void TimerAutoStartSpy::RegisterCallback(TimerAutoStartCallbackInterface* callback)
{
    RegisterCallbackCalled = true;
    RegisteredCallback = callback;
}
