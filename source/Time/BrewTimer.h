#pragma once

#include <array>
#include <cstddef>

#include "BrewTimerInterface.h"
#include "SystemInterface.h"

namespace coffeescales::time
{

class BrewTimer : public BrewTimerInterface
{
  public:
    BrewTimer(halwrapper::SystemInterface& system);
    void Task();
    void Start();
    void Reset();
    bool RegisterCallback(TimerIncrementCallbackInterface* callback);

  protected:
    static constexpr size_t MaxCallbacks = 32;
    uint32_t mCallbackCount = 0;
    std::array<TimerIncrementCallbackInterface*, MaxCallbacks> mCallbacks;

  private:
    void UpdateSubscribers();

  private:
    halwrapper::SystemInterface& mSystem;
    bool mRunning = false;
    uint32_t mStartTick = 0;
    uint32_t mMinutes = 0;
    uint32_t mSeconds = 0;
};

}