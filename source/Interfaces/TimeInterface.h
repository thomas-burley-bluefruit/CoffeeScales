#pragma once

#include <cstdint>

namespace coffeescales::halwrapper
{

class TimeInterface
{
public:
    ~TimeInterface() = default;
    virtual void DelayMs(const uint32_t delayMs) = 0;
    virtual void DelayUs(const uint16_t delayUs) = 0;
    virtual uint32_t GetTick() const = 0;
};

}