#pragma once

#include "ButtonDriverInterface.h"
#include "ButtonPressCallbackInterface.h"
#include "PourRateInterface.h"
#include "ScalesInterface.h"
#include "TimeInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::weight
{

class PourRate :
    public PourRateInterface,
    public WeightReadingCallbackInterface,
    public drivers::ButtonPressCallbackInterface
{
  public:
    PourRate(ScalesInterface& scales, halwrapper::TimeInterface& time,
        drivers::ButtonDriverInterface& tareButton);

    // PourRateInterface
    void RegisterCallback(PourRateUpdateCallbackInterface* callback) override;

    // WeightReadingCallbackInterface
    void NewWeightReadingMg(int32_t weightMg);

    // ButtonPressCallbackInterface
    void OnButtonPress(const drivers::buttons::Button button, const uint32_t tickMs = 0);

    static constexpr float FilterTimeConstant = 0.8f;
    static constexpr size_t AveragingSampleCount = 20;

  private:
    halwrapper::TimeInterface& mTime;
    PourRateUpdateCallbackInterface* mCallback;

    uint32_t mLastWeightReadingTickMs = 0;
    int32_t mLastWeightReadingMg = 0;
    float mLastPourRateCalculatedGramsPerSec = 0;
    float mLastPourRateIssuedGramsPerSec = 0;

    float CalculatePourRate(int32_t newReadingMg);
    float FilterPourRate(float gramsPerSec);
};

}
