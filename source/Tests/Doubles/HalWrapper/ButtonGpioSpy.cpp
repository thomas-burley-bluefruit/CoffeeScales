#include "ButtonGpioSpy.h"

using namespace ::coffeescales::halwrapper;

void ButtonGpioSpy::RegisterCallback(ExternalInterruptCallbackInterface *callback)
{
    RegisterCallbackCalled = true;
    Callback = callback;
}
