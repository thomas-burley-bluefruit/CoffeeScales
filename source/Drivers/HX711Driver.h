#pragma once

#include "SystemInterface.h"
#include "HX711DriverInterface.h"

namespace drivers
{

class HX711Driver final : public HX711DriverInterface
{
public:
    HX711Driver(halwrapper::SystemInterface& system);
    ~HX711Driver() = default;

    bool ReadAdcValue(int32_t &value) const override;

    static constexpr uint16_t TimingDelayUs = 1;
    static constexpr uint32_t AdcBits = 24;
    static constexpr uint32_t AdcSignBit = 1 << (AdcBits - 1);
    static constexpr uint32_t AdcMsb = AdcSignBit >> 1;

private:
    halwrapper::SystemInterface& mSystem;
};

}