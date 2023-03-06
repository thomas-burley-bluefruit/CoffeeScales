#pragma once

#include "HX711Gpio.h"
#include "Delay.h"
#include "SystemInterface.h"

namespace halwrapper
{

class System final : public SystemInterface, private HX711Gpio, private Delay
{
public:
    ~System() = default;
    void Init();
    void DelayMs(const uint32_t delayMs) override;
    void DelayUs(const uint16_t delayUs) override;
    GpioPinState GetPinState() const override;
    void SetPinState(const GpioPinState state) override;
};

}