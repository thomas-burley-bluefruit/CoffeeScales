#pragma once

#include "TimerAutoStartInterface.h"

namespace coffeescales::time
{

class TimerAutoStartSpy : public TimerAutoStartInterface
{
  public:
    void Enable() override;
    void RegisterCallback(TimerAutoStartCallbackInterface* callback) override;

    bool EnableCalled = false;

    bool RegisterCallbackCalled = false;
    TimerAutoStartCallbackInterface* RegisteredCallback = nullptr;
};

}