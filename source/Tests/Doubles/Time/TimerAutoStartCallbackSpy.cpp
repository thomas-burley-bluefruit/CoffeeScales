#include "TimerAutoStartCallbackSpy.h"

using namespace coffeescales::time;

void TimerAutoStartCallbackSpy::TimerAutoStartEnabled(bool enabled)
{
    TimerAutoStartEnabledCalled = true;
    TimerAutoStartEnabledValue = enabled;
}
