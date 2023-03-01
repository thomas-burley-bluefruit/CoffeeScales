#pragma once

#include "Types.h"

namespace halwrapper
{

class HX711GpioInterface
{
public:
    ~HX711GpioInterface() = default;
    virtual GpioPinState GetDataPinState() const = 0;
    virtual void SetClockPin(const GpioPinState state) = 0;
};

}