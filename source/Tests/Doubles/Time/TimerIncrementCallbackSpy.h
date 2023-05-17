#pragma once

#include "TimerIncrementCallbackInterface.h"

namespace coffeescales::time
{

class TimerIncrementCallbackSpy : public TimerIncrementCallbackInterface
{
public:
    void TimeUpdate(uint32_t minutes, uint32_t seconds) override;

    uint32_t LastMinutes = 0;
    uint32_t LastSeconds = 0;
    size_t CallCount = 0;
};

}
