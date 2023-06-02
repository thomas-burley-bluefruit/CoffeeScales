#pragma once

#include "TimerAutoStartCallbackInterface.h"

namespace coffeescales::time
{

class TimerAutoStartInterface
{
  public:
    virtual void Enable() = 0;
    virtual void RegisterCallback(TimerAutoStartCallbackInterface* callback) = 0;
};

}