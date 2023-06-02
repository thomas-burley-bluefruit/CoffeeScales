#pragma once

#include "TimerAutoStartCallbackInterface.h"

namespace coffeescales::time
{

class TimerAutoStartCallbackSpy : public TimerAutoStartCallbackInterface
{
  public:
    void TimerAutoStartEnabled(bool enabled) override;

    bool TimerAutoStartEnabledCalled = false;
    bool TimerAutoStartEnabledValue = false;
};

}