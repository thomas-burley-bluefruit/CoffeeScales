#pragma once

#include "SystemInterface.h"
#include "AdcDriverInterface.h"

namespace coffeescales::drivers
{

class HX711Driver final : public AdcDriverInterface
{
public:
    explicit HX711Driver(halwrapper::SystemInterface &system);
    ~HX711Driver() = default;

    bool Read(int32_t &value) const override;
    [[nodiscard]] uint32_t MaxValue() const override;

    static constexpr uint16_t TimingDelayUs = 1;
    static constexpr uint32_t AdcBits = 24;

private:
    halwrapper::SystemInterface &mSystem;
};

}