#pragma once

#include <array>
#include <cstddef>

#include "BrewTimerInterface.h"
#include "ButtonDriverInterface.h"
#include "ButtonPressCallbackInterface.h"
#include "SystemInterface.h"
#include "TerminalInterface.h"

namespace coffeescales::time
{

class BrewTimer : public BrewTimerInterface, public drivers::ButtonPressCallbackInterface
{
  public:
    BrewTimer(halwrapper::SystemInterface& system, drivers::ButtonDriverInterface& timerButton);

    void Init();

    // BrewTimerInterface
    void Task();
    void Start();
    void Reset();
    bool RegisterCallback(TimerIncrementCallbackInterface* callback);

    // ButtonPressCallbackInterface
    void OnButtonPress(const drivers::buttons::Button button, const uint32_t tickMs = 0);

  protected:
    static constexpr size_t MaxCallbacks = 32;
    uint32_t mCallbackCount = 0;
    std::array<TimerIncrementCallbackInterface*, MaxCallbacks> mCallbacks;

  private:
    void UpdateSubscribers();

  private:
    halwrapper::SystemInterface& mSystem;
    drivers::ButtonDriverInterface& mTimerButton;
    bool mRunning = false;
    bool mStartRequested = false;
    bool mResetRequested = false;
    uint32_t mStartTick = 0;
    uint32_t mMinutes = 0;
    uint32_t mSeconds = 0;

    void ActionStart();
    void ActionReset();
};

}
