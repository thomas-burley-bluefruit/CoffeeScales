#pragma once

#include "ExternalInterruptCallbackInterface.h"

namespace coffeescales::halwrapper
{

class ExternalInterruptCallbackRegisterableInterface
{
  public:
    virtual void RegisterCallback(ExternalInterruptCallbackInterface* callback) = 0;
};

}