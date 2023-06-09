#pragma once

#include "PourRateUpdateCallbackInterface.h"

namespace coffeescales::weight
{

class PourRateUpdateCallbackSpy : public PourRateUpdateCallbackInterface
{
  public:
    void PourRateUpdate(float gramsPerSecond);

    bool PourRateUpdateCalled = false;
    float GramsPerSecond = 0;
};

}