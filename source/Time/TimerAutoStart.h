#pragma once

#include "BrewTimerInterface.h"
#include "ScalesInterface.h"
#include "TimerAutoStartCallbackInterface.h"
#include "TimerAutoStartInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::time
{

class TimerAutoStart : public TimerAutoStartInterface, public weight::WeightReadingCallbackInterface
{
  public:
    TimerAutoStart(BrewTimerInterface& brewTimer, weight::ScalesInterface& scales);

    // TimerAutoStartInterface
    void Enable() override;
    void RegisterCallback(TimerAutoStartCallbackInterface* callback) override;

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