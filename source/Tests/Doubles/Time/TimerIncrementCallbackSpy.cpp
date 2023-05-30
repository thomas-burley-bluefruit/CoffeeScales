#include "TimerIncrementCallbackSpy.h"

using namespace coffeescales::time;

void TimerIncrementCallbackSpy::TimeUpdate(uint32_t minutes, uint32_t seconds)
{
    LastMinutes = minutes;
    LastSeconds = seconds;
    CallCount++;
}
