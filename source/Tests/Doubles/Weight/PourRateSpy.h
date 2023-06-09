#pragma once

#include "PourRateInterface.h"

namespace coffeescales::weight
{

class PourRateSpy : public PourRateInterface
{
  public:
    void RegisterCallback(PourRateUpdateCallbackInterface* callback);

    bool RegisterCallbackCalled = false;
    PourRateUpdateCallbackInterface* RegisteredCallback = nullptr;
};

}
