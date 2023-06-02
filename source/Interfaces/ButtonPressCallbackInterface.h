#pragma once

#include "Buttons.h"
#include "GpioPinState.h"

#include <cstdint>

namespace coffeescales::drivers
{

class ButtonPressCallbackInterface
{
  public:
    ~ButtonPressCallbackInterface() = default;
    virtual void OnButtonPress(const buttons::Button button, const uint32_t tickMs) = 0;
};

}