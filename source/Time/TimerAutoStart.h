#pragma once

#include "BrewTimerInterface.h"
#include "ButtonDriverInterface.h"
#include "ButtonPressCallbackInterface.h"
#include "ScalesInterface.h"
#include "TimerAutoStartCallbackInterface.h"
#include "TimerAutoStartInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::time
{

class TimerAutoStart :
    public TimerAutoStartInterface,
    public weight::WeightReadingCallbackInterface,
    public drivers::ButtonPressCallbackInterface
{
  public:
    TimerAutoStart(BrewTimerInterface& brewTimer, weight::ScalesInterface& scales,
        drivers::ButtonDriverInterface& timerButton);

    // TimerAutoStartInterface
    void Enable() override;
    void RegisterCallback(TimerAutoStartCallbackInterface* callback) override;

    // WeightReadingCallbackInterface
    void NewWeightReadingMg(int32_t weightMg) override;

    // ButtonPressCallbackInterface
    void OnButtonPress(const drivers::buttons::Button button, const uint32_t tickMs);

    static constexpr int32_t ThresholdMg = 150;
    static constexpr uint32_t DoubleClickWindowMs = 400;

  private:
    BrewTimerInterface& mBrewTimer;
    TimerAutoStartCallbackInterface* mCallback = nullptr;

    bool mEnabled = false;
    int32_t mLastWeightReadingMg = 0;
    int32_t mReferenceWeightMg = 0;
    uint32_t mLastButtonPressTickMs = DoubleClickWindowMs;
};

}