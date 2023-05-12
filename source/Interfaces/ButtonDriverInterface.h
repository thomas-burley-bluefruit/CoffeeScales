#pragma once

#include "ButtonPressCallbackInterface.h"

namespace coffeescales::drivers
{

class ButtonDriverInterface
{
public:
    ~ButtonDriverInterface() = default;
    virtual void RegisterCallback(ButtonPressCallbackInterface *callback) = 0;
};

}