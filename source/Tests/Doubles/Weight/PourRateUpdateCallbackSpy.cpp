#include "PourRateUpdateCallbackSpy.h"

using namespace ::coffeescales::weight;

void PourRateUpdateCallbackSpy::PourRateUpdate(uint32_t gramsPerSecond)
{
    PourRateUpdateCalled = true;
    GramsPerSecond = gramsPerSecond;
}