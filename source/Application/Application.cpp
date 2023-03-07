#include "Application.h"
#include "Instantiation.h"

#include <string>

static Instantiation mInstantiation;

void Application_Init()
{
    mInstantiation.Init();
}

void Application_Loop()
{
    while (1)
    {
        int32_t adcReading = 0;
        const auto adcResult = mInstantiation.Hx711().ReadAdcValue(adcReading);
        if (adcResult) {
            char buffer[32];
            snprintf(buffer, 32, "ADC: %li\n", adcReading);
            mInstantiation.Terminal().TextOut(buffer);
        }
        mInstantiation.System().DelayMs(100);
    }
}
