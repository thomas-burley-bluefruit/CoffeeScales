#pragma once

namespace coffeescales::time
{

class TimerAutoStartCallbackInterface
{
  public:
    ~TimerAutoStartCallbackInterface() = default;
    virtual void TimerAutoStartEnabled(bool enabled) = 0;
};

}