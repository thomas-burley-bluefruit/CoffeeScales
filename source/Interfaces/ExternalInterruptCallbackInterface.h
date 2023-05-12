#pragma once

#include "GpioPinState.h"

namespace coffeescales::halwrapper
{

class ExternalInterruptCallbackInterface
{
public:
    ~ExternalInterruptCallbackInterface() = default;
    virtual void OnExternalInterrupt() = 0;
};

}