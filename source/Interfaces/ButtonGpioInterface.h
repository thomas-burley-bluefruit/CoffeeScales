#pragma once

#include "ExternalInterruptCallbackInterface.h"

namespace coffeescales::halwrapper
{

class ButtonGpioInterface
{
public:
    virtual void RegisterCallback(ExternalInterruptCallbackInterface *callback) = 0;
};

}