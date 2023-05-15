#pragma once

#include "ButtonDriverInterface.h"

namespace coffeescales::drivers
{

class ButtonDriverSpy final : public ButtonDriverInterface
{
public:
    void RegisterCallback(ButtonPressCallbackInterface *callback) override;

    bool RegisterCallbackCalled = false;
    ButtonPressCallbackInterface *Callback = nullptr;
};

}
