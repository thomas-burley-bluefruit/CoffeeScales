#pragma once

#include <cstdint>

namespace halwrapper
{

class DelayInterface
{
public:
    ~DelayInterface() = default;
    virtual void DelayMs(uint32_t delayMs) = 0;
    virtual void DelayUs(uint16_t delayUs) = 0;
};

}