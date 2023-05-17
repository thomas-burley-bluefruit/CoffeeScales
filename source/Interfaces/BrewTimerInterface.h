#pragma once

#include "TimerIncrementCallbackInterface.h"

namespace coffeescales::time
{

class BrewTimerInterface
{
public:
  ~BrewTimerInterface() = default;
  virtual void StartTimer() = 0;
  virtual void ResetTimer() = 0;
  virtual bool RegisterCallback(TimerIncrementCallbackInterface *callback) = 0;
};

}