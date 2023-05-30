#pragma once

#include "ButtonGpioInterface.h"
#include "ExternalInterruptCallbackInterface.h"

namespace coffeescales::halwrapper
{

class TimerButtonGpio final : public ButtonGpioInterface
{
  public:
    void Init();
    void RegisterCallback(ExternalInterruptCallbackInterface* callback) override;
};

}
