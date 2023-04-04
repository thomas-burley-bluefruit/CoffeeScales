#pragma once

#include <cstdint>

namespace coffeescales::weight
{

class WeightReadingCallbackInterface
{
public:
    ~WeightReadingCallbackInterface() = default;
    virtual void NewWeightReadingMg(int32_t weightMg) = 0;
};

}
