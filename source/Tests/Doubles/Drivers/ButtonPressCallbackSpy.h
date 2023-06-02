#pragma once

#include "ButtonPressCallbackInterface.h"

namespace coffeescales::drivers
{

class ButtonPressCallbackSpy final : public ButtonPressCallbackInterface
{
  public:
    void Reset();
    void OnButtonPress(const buttons::Button button, const uint32_t tickMs) override;

    bool OnButtonPressCalled = false;
    buttons::Button Button = buttons::Button::Count;
    uint32_t TickMs = 0;
};

}
