#include "HX711Driver.h"

using namespace drivers;
using namespace halwrapper;

HX711Driver::HX711Driver(SystemInterface& system) : mSystem(system)
{}

bool HX711Driver::ReadAdcValue(int32_t &value) const
{
    if (mSystem.GetPinState() == GpioPinState::Set)
        return false;

    int32_t adcValue = 0;
    for (uint32_t i = AdcMsb; i > 0; i >>= 1)
    {
        mSystem.SetPinState(GpioPinState::Set);
        mSystem.DelayUs(TimingDelayUs);
        if (mSystem.GetPinState() == GpioPinState::Set)
            adcValue |= i;
        mSystem.SetPinState(GpioPinState::Reset);
        mSystem.DelayUs(TimingDelayUs);
    }

    mSystem.SetPinState(GpioPinState::Set);
    mSystem.DelayUs(TimingDelayUs);
    mSystem.SetPinState(GpioPinState::Reset);

    value = adcValue;
    return true;
}
