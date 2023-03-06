#pragma once

#include "SystemInterface.h"
#include "HX711Driver.h"

#include <cstdint>
#include <vector>

namespace halwrapper
{

enum class SystemInterfaceMethod
{
    GetPinState,
    SetPinState,
    DelayUs
};

struct SystemInterfaceCall
{
    SystemInterfaceMethod method;
    union
    {
        GpioPinState gpioState;
        uint16_t delayUs;
    };
    bool operator==(const SystemInterfaceCall& rhs) const
    {
        return this->method == rhs.method &&
               this->delayUs == rhs.delayUs;
    }
};

class SystemMock final : public SystemInterface
{
public:
    GpioPinState GetPinState() const override;
    void SetPinState(const GpioPinState state) override;
    void DelayMs(const uint32_t delayMs) override;
    void DelayUs(const uint16_t delayUs) override;

    mutable std::vector<SystemInterfaceCall> Calls;
    bool DataAvailable = false;
    GpioPinState SetClockPinState = GpioPinState::Reset;
    mutable bool ClockRisingEdge = false;
    int32_t AdcValue = 0;
    mutable uint32_t ReadIndex = drivers::HX711Driver::AdcMsb;
};

}