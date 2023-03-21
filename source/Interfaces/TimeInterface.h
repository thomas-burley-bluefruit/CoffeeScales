#pragma once

#include <cstdint>

namespace coffeescales::halwrapper
{

class TimeInterface
{
public:
    ~TimeInterface() = default;
    virtual void DelayMs(uint32_t delayMs) = 0;
    virtual void DelayUs(uint16_t delayUs) = 0;
    [[nodiscard]] virtual uint32_t GetTick() const = 0;
};

}