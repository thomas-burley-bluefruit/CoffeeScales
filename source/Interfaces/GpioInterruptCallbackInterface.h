#pragma once

#include "GpioPinState.h"

namespace coffeescales::halwrapper
{

class GpioInterruptCallbackInterface
{
public:
    ~GpioInterruptCallbackInterface() = default;
    virtual void OnReceiveInterrupt() = 0;
};

}