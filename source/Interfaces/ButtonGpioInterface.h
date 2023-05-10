#pragma once

#include "GpioInterruptCallbackInterface.h"

namespace coffeescales::halwrapper
{

class ButtonGpioInterface
{
public:
    virtual void SetCallback(GpioInterruptCallbackInterface *callback) = 0;
};

}