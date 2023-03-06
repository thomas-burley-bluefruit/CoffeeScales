#include "Delay.h"
#include "stm32l4xx_hal.h"

using namespace ::halwrapper;

void Delay::DelayUs(const uint16_t delayUs)
{
    ResetCounter();
    while (GetCounter() < delayUs);
}

void Delay::DelayMs(uint32_t delayMs)
{
    HAL_Delay(delayMs);
}