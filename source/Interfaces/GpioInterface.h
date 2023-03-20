#pragma once

#include "Types.h"

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