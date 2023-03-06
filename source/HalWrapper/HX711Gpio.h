#pragma once
#include "GpioInterface.h"
#include "DelayInterface.h"

namespace halwrapper
{

class HX711Gpio : public GpioInterface
{
public:
    void Init();
    GpioPinState GetPinState() const override;
    void SetPinState(const GpioPinState state) override;
};

}