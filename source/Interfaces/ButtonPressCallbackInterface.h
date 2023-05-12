#pragma once

#include "Buttons.h"
#include "GpioPinState.h"

namespace coffeescales::drivers
{

class ButtonPressCallbackInterface
{
public:
    ~ButtonPressCallbackInterface() = default;
    virtual void OnButtonPress(buttons::Button button) = 0;
};

}