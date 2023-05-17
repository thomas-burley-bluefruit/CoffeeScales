#pragma once

#include <array>
#include <cstddef>

#include "BrewTimerInterface.h"
#include "SystemInterface.h"

namespace coffeescales::time
{

class BrewTimer final : public BrewTimerInterface
{
public:
  BrewTimer(halwrapper::SystemInterface& system);
  void Task();
  void StartTimer();
  void ResetTimer();
  bool RegisterCallback(TimerIncrementCallbackInterface *callback);

protected:
    static constexpr size_t MaxCallbacks = 32;
    uint32_t mCallbackCount = 0;
    std::array<TimerIncrementCallbackInterface *, MaxCallbacks> mCallbacks;

private:
  halwrapper::SystemInterface& mSystem;
};

}