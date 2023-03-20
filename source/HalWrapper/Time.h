#pragma once

#include "TimeInterface.h"
#include "DelayTimer.h"

#include <cstdint>

namespace coffeescales::halwrapper
{

class Time : public DelayTimer, public TimeInterface
{
public:
    void DelayUs(uint16_t delayUs) override;
    void DelayMs(uint32_t delayMs) override;
    [[nodiscard]] uint32_t GetTick() const override;
};

}