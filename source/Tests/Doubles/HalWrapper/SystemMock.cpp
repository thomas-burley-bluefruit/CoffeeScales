#include "SystemMock.h"

using namespace coffeescales::drivers;
using namespace coffeescales::halwrapper;

GpioPinState SystemMock::GetPinState() const {
    Calls.push_back({ SystemInterfaceMethod::GetPinState });

    if (!DataAvailable)
        return GpioPinState::Set;

    if (!ClockRisingEdge)
        return GpioPinState::Reset;

    ClockRisingEdge = false;

    bool pinState = AdcData[ReadIndex];
    if (ReadIndex == 0)
        ReadIndex = HX711Driver::AdcBits - 1;
    else
        --ReadIndex;
    return pinState ? GpioPinState::Set : GpioPinState::Reset;
}

void SystemMock::SetPinState(const halwrapper::GpioPinState state) {
    Calls.push_back({ .method = SystemInterfaceMethod::SetPinState, .gpioState = state });

    if (state == GpioPinState::Set && SetClockPinState == GpioPinState::Reset)
        ClockRisingEdge = true;
    SetClockPinState = state;
}

void SystemMock::DelayMs(const uint32_t delayMs)
{
}

void SystemMock::DelayUs(const uint16_t delayUs)
{
    Calls.push_back({ .method = SystemInterfaceMethod::DelayUs, .delayUs = delayUs });
}
