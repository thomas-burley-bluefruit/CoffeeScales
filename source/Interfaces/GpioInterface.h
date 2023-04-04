#pragma once

#include "GpioPinState.h"

#include <cstdint>

namespace coffeescales::halwrapper
{

class GpioInterface
{
public:
    ~GpioInterface() = default;
    [[nodiscard]] virtual GpioPinState GetPinState() const = 0;
    virtual void SetPinState(GpioPinState state) = 0;
};

}