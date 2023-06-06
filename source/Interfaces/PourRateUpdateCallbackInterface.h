#pragma once

#include <cstdint>

namespace coffeescales::weight
{

class PourRateUpdateCallbackInterface
{
  public:
    ~PourRateUpdateCallbackInterface() = default;
    virtual void PourRateUpdate(uint32_t gramsPerSecond) = 0;
};

}
