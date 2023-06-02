#pragma once

#include "ExternalInterruptCallbackRegisterableInterface.h"

namespace coffeescales::halwrapper
{

class ExternalInterruptCallbackRegisterableSpy final :
    public ExternalInterruptCallbackRegisterableInterface
{
  public:
    void RegisterCallback(ExternalInterruptCallbackInterface* callback) override;

    bool RegisterCallbackCalled = false;
    ExternalInterruptCallbackInterface* Callback = nullptr;
};

}
