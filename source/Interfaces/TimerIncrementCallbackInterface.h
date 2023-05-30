#pragma once

#include <cstdint>

namespace coffeescales::time
{

class TimerIncrementCallbackInterface
{
public:
    ~TimerIncrementCallbackInterface() = default;
    virtual void TimeUpdate(uint32_t minutes, uint32_t seconds) = 0;
};

}
