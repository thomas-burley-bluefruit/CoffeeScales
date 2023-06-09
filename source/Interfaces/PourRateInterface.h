#pragma once

#include "PourRateUpdateCallbackInterface.h"

namespace coffeescales::weight
{

class PourRateInterface
{
  public:
    ~PourRateInterface() = default;
    virtual void RegisterCallback(PourRateUpdateCallbackInterface* callback) = 0;
};

}
