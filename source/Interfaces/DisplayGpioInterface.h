#pragma once

#include "SpiInterface.h"
#include "GpioPinState.h"

namespace coffeescales::halwrapper
{

class DisplayGpioInterface : public SpiInterface
{
public:
    ~DisplayGpioInterface() = default;
    virtual void SetResetPin(GpioPinState state) = 0;
};

}