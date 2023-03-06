#include "System.h"

using namespace ::halwrapper;

void System::Init()
{
    Delay::Init();
    HX711Gpio::Init();
}

void System::DelayMs(const uint32_t delayMs)
{
    Delay::DelayMs(delayMs);
}

void System::DelayUs(const uint16_t delayUs)
{
    Delay::DelayUs(delayUs);
}

GpioPinState System::GetPinState() const {
    return HX711Gpio::GetPinState();
}

void System::SetPinState(const halwrapper::GpioPinState state) {
    HX711Gpio::SetPinState(state);
}