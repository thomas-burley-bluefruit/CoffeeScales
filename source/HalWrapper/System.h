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
    void DelayMs(uint32_t delayMs) override;
    void DelayUs(uint16_t delayUs) override;
    [[nodiscard]] uint32_t GetTick() const override;
    [[nodiscard]] GpioPinState GetPinState() const override;
    void SetPinState(GpioPinState state) override;
};

}