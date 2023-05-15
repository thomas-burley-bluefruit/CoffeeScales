#pragma once

#include "ExternalInterruptCallbackInterface.h"
#include "ButtonGpioInterface.h"

namespace coffeescales::halwrapper
{

class TareButtonGpio final : public ButtonGpioInterface
{
public:
    void Init();
    void RegisterCallback(ExternalInterruptCallbackInterface *callback) override;
};

}
