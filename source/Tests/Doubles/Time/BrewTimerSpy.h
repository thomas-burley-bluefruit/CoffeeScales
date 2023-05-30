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

    bool RegisterCallbackCalled = false;
    TimerIncrementCallbackInterface* RegisteredCallback = nullptr;
};

}