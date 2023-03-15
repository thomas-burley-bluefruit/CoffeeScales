#pragma once

#include "HX711Gpio.h"
#include "Time.h"
#include "SystemInterface.h"

namespace coffeescales::halwrapper
{

class System final : public SystemInterface, private HX711Gpio, private Time
{
public:
    ~System() = default;
    void Init();
    void DelayMs(const uint32_t delayMs) override;
    void DelayUs(const uint16_t delayUs) override;
    uint32_t GetTick() const override;
    GpioPinState GetPinState() const override;
    void SetPinState(const GpioPinState state) override;
};

}