#pragma once

#include "TimerIncrementCallbackInterface.h"

namespace coffeescales::time
{

class BrewTimerInterface
{
public:
  ~BrewTimerInterface() = default;
  virtual void Start() = 0;
  virtual void Reset() = 0;
  virtual bool RegisterCallback(TimerIncrementCallbackInterface *callback) = 0;
};

}