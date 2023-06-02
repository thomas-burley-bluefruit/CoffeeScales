#pragma once

#include "BrewTimerInterface.h"

namespace coffeescales::time
{

class BrewTimerSpy : public BrewTimerInterface
{
  public:
    void Start() override;
    void Reset() override;
    bool RegisterCallback(TimerIncrementCallbackInterface* callback) override;

    bool StartCalled = false;
    bool ResetCalled = false;

    bool RegisterCallbackCalled = false;
    TimerIncrementCallbackInterface* RegisteredCallback = nullptr;
};

}