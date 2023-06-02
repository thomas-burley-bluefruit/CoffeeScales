#include "ExternalInterruptCallbackRegisterableSpy.h"

using namespace ::coffeescales::halwrapper;

void ExternalInterruptCallbackRegisterableSpy::RegisterCallback(
    ExternalInterruptCallbackInterface* callback)
{
    RegisterCallbackCalled = true;
    Callback = callback;
}
