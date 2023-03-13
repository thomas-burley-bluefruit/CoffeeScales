#include "HX711Driver.h"
#include "Utilities.h"

#include <bitset>

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;
using std::bitset;

HX711Driver::HX711Driver(SystemInterface& system) : mSystem(system)
{}

bool HX711Driver::Read(int32_t &value) const
{
    if (mSystem.GetPinState() == GpioPinState::Set)
        return false;

    bitset<AdcBits> adcData;
    for (uint32_t i = AdcBits; i > 0; --i)
    {
        mSystem.SetPinState(GpioPinState::Set);
        mSystem.DelayUs(TimingDelayUs);
        if (mSystem.GetPinState() == GpioPinState::Set)
            adcData.set(i - 1);
        mSystem.SetPinState(GpioPinState::Reset);
        mSystem.DelayUs(TimingDelayUs);
    }

    mSystem.SetPinState(GpioPinState::Set);
    mSystem.DelayUs(TimingDelayUs);
    mSystem.SetPinState(GpioPinState::Reset);

    value = Utilities::TwosComplementToInt(adcData);
    return true;
}
