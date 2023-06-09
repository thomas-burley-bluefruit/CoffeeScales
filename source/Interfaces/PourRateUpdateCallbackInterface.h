#pragma once

#include <cstdint>

namespace coffeescales::weight
{

class PourRateUpdateCallbackInterface
{
  public:
    ~PourRateUpdateCallbackInterface() = default;
    virtual void PourRateUpdate(float gramsPerSecond) = 0;
};

}
