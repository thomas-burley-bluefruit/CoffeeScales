#pragma once

#include "GpioInterface.h"
#include "TimeInterface.h"

namespace coffeescales::halwrapper
{

class HX711Gpio : public GpioInterface
{
public:
    static void Init();
    [[nodiscard]] GpioPinState GetPinState() const override;
    void SetPinState(GpioPinState state) override;
};

}