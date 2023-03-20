#include "System.h"

using namespace ::coffeescales::halwrapper;

void System::Init()
{
    Time::Init();
    HX711Gpio::Init();
}

void System::DelayMs(const uint32_t delayMs)
{
    Time::DelayMs(delayMs);
}

void System::DelayUs(const uint16_t delayUs)
{
    Time::DelayUs(delayUs);
}

uint32_t System::GetTick() const
{
    return Time::GetTick();
}

GpioPinState System::GetPinState() const
{
    return HX711Gpio::GetPinState();
}

void System::SetPinState(const halwrapper::GpioPinState state)
{
    HX711Gpio::SetPinState(state);
}