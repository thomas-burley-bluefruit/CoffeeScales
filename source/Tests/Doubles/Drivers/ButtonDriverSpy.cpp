#include "ButtonDriverSpy.h"

using namespace ::coffeescales::drivers;

void ButtonDriverSpy::RegisterCallback(
        ButtonPressCallbackInterface *callback)
{
    RegisterCallbackCalled = true;
    Callback = callback;
}
