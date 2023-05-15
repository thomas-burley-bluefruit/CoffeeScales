#pragma once

#include "ButtonGpioInterface.h"

namespace coffeescales::halwrapper
{

class ButtonGpioSpy final : public ButtonGpioInterface
{
public:
    void RegisterCallback(ExternalInterruptCallbackInterface *callback) override;

    bool RegisterCallbackCalled = false;
    ExternalInterruptCallbackInterface *Callback = nullptr;
};

}

