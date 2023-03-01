#pragma once
#include "TerminalInterface.h"
#include "HX711GpioInterface.h"
#include "DelayInterface.h"

namespace halwrapper
{

class HX711Gpio : public HX711GpioInterface
{
public:
    void Init();
    GpioPinState GetDataPinState() const override;
    void SetClockPin(const GpioPinState state) override;
};

}