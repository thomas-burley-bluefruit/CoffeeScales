#pragma once

#include "GpioInterface.h"

namespace coffeescales::halwrapper
{

class GpioSpy : public GpioInterface
{
  public:
    [[nodiscard]] GpioPinState GetPinState() const;
    void SetPinState(GpioPinState state);

    mutable bool GetPinStateCalled = false;
    GpioPinState GetPinStateValue = GpioPinState::Reset;

    bool SetPinStateCalled = false;
    GpioPinState SetPinStateValue = GpioPinState::Reset;
};

}