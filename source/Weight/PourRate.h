#pragma once

#include "PourRateInterface.h"
#include "ScalesInterface.h"
#include "TimeInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::weight
{

class PourRate : public PourRateInterface, public WeightReadingCallbackInterface
{
  public:
    PourRate(ScalesInterface& scales, halwrapper::TimeInterface& time);

    // PourRateInterface
    void RegisterCallback(PourRateUpdateCallbackInterface* callback) override;

    // WeightReadingCallbackInterface
    void NewWeightReadingMg(int32_t weightMg);

  private:
    halwrapper::TimeInterface& mTime;
    PourRateUpdateCallbackInterface* mCallback;
    uint32_t mLastWeightReadingTickMs = 0;
    int32_t mLastWeightReadingMg = 0;
    uint32_t mLastPourRateCalculated = 0;

    uint32_t CalculatePourRate(int32_t newReadingMg);
};

}
