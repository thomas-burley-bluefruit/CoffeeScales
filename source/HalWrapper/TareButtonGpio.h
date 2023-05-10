#pragma once

#include "GpioInterruptCallbackInterface.h"
#include "ButtonGpioInterface.h"

namespace coffeescales::halwrapper
{

class TareButtonGpio final : public ButtonGpioInterface
{
public:
    void Init();
    void SetCallback(GpioInterruptCallbackInterface *callback) override;
};

}
