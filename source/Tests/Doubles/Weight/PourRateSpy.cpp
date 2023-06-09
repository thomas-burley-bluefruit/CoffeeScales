#include "PourRateSpy.h"

using namespace ::coffeescales::weight;

void PourRateSpy::RegisterCallback(PourRateUpdateCallbackInterface* callback)
{
    RegisterCallbackCalled = true;
    RegisteredCallback = callback;
}