#pragma once

#include "WeightReadingCallbackInterface.h"

namespace coffeescales::weight
{

class WeightReadingCallbackSpy : public WeightReadingCallbackInterface
{
public:
    void NewWeightReadingMg(int32_t weightMg) override;

    int32_t LastWeightReading = 0;
    size_t CallCount = 0;
};

}
