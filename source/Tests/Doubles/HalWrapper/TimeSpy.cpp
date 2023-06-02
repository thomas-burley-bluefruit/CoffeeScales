#include "TimeSpy.h"

using namespace ::coffeescales::halwrapper;

void TimeSpy::DelayMs(uint32_t delayMs)
{
    DelayMsCalled = true;
    DelayMsValue = delayMs;
}

void TimeSpy::DelayUs(uint16_t delayUs)
{
    DelayUsCalled = true;
    DelayUsValue = delayUs;
}

[[nodiscard]] uint32_t TimeSpy::GetTick() const
{
    GetTickCalled = true;
    return GetTickValue;
}
