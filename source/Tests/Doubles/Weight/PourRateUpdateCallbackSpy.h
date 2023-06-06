#pragma once

#include "PourRateUpdateCallbackInterface.h"

namespace coffeescales::weight
{

class PourRateUpdateCallbackSpy : public PourRateUpdateCallbackInterface
{
  public:
    void PourRateUpdate(uint32_t gramsPerSecond);

    bool PourRateUpdateCalled = false;
    uint32_t GramsPerSecond = 0;
};

}