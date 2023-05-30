#pragma once

#include "BrewTimerInterface.h"
#include "ScalesInterface.h"
#include "TimerAutoStartCallbackInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::time
{

class TimerAutoStart : public weight::WeightReadingCallbackInterface
{
  public:
    TimerAutoStart(BrewTimerInterface& brewTimer, weight::ScalesInterface& scales);
    void Enable();
    void RegisterCallback(TimerAutoStartCallbackInterface* callback);

    // WeightReadingCallbackInterface
    void NewWeightReadingMg(int32_t weightMg) override;

    static constexpr uint32_t ThresholdMg = 150;

  private:
    BrewTimerInterface& mBrewTimer;
    weight::ScalesInterface& mScales;
    TimerAutoStartCallbackInterface* mCallback = nullptr;

    bool mEnabled = false;
    int32_t mLastWeightReadingMg = 0;
    int32_t mReferenceWeightMg = 0;
};

}