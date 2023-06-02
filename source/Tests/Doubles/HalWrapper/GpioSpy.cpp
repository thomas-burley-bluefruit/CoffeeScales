#include "GpioSpy.h"

using namespace coffeescales::halwrapper;

GpioPinState GpioSpy::GetPinState() const
{
    GetPinStateCalled = true;
    return GetPinStateValue;
}

void GpioSpy::SetPinState(GpioPinState state)
{
    SetPinStateCalled = true;
    SetPinStateValue = state;
}
