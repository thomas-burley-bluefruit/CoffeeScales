#pragma once

#include "ExternalInterruptCallbackRegisterableInterface.h"

namespace coffeescales::halwrapper
{

class InterruptTimerGpio : public ExternalInterruptCallbackRegisterableInterface
{
  public:
    void Init();

    // ExternalInterruptCallbackRegisterableInterface
    void RegisterCallback(ExternalInterruptCallbackInterface* callback);
};

}