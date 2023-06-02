#pragma once

#include "TimeInterface.h"

namespace coffeescales::halwrapper
{

class TimeSpy : public TimeInterface
{
  public:
    void DelayMs(uint32_t delayMs);
    void DelayUs(uint16_t delayUs);
    [[nodiscard]] uint32_t GetTick() const;

    bool DelayMsCalled = false;
    uint32_t DelayMsValue = 0;

    bool DelayUsCalled = false;
    uint16_t DelayUsValue = 0;

    mutable bool GetTickCalled = false;
    uint32_t GetTickValue = 0;
};

}