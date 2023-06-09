#include "PourRateUpdateCallbackSpy.h"

using namespace ::coffeescales::weight;

void PourRateUpdateCallbackSpy::PourRateUpdate(float gramsPerSecond)
{
    PourRateUpdateCalled = true;
    GramsPerSecond = gramsPerSecond;
}