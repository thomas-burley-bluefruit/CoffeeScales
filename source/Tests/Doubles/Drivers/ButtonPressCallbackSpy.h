#pragma once

#include "ButtonPressCallbackInterface.h"

namespace coffeescales::drivers
{

class ButtonPressCallbackSpy final : public ButtonPressCallbackInterface
{
public:
    void Reset();
    void OnButtonPress(buttons::Button button) override;

    bool OnButtonPressCalled = false;
    buttons::Button Button = buttons::Button::Count;
};

}
