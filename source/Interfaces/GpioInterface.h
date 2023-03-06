#pragma once

#include "Types.h"

#include <cstdint>

namespace halwrapper
{

class GpioInterface
{
public:
    ~GpioInterface() = default;
    virtual GpioPinState GetPinState() const = 0;
    virtual void SetPinState(const GpioPinState state) = 0;
};

}