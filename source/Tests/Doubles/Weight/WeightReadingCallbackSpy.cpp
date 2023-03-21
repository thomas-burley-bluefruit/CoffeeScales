#include "WeightReadingCallbackSpy.h"

using namespace ::coffeescales::weight;

void WeightReadingCallbackSpy::NewWeightReadingMg(int32_t weightMg)
{
    CallCount++;
    LastWeightReading = weightMg;
}
