#include "Time.h"
#include "stm32l4xx_hal.h"

using namespace ::coffeescales::halwrapper;

void Time::DelayUs(const uint16_t delayUs)
{
    ResetCounter();
    while (GetCounter() < delayUs);
}

void Time::DelayMs(uint32_t delayMs)
{
    HAL_Delay(delayMs);
}

uint32_t Time::GetTick() const
{
    return HAL_GetTick();
}
