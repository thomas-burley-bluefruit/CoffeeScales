#pragma once

#include "DelayInterface.h"
#include "DelayTimer.h"

#include <cstdint>

namespace halwrapper
{

class Delay : public DelayTimer, public DelayInterface
{
public:
    void DelayUs(const uint16_t delayUs) override;
    void DelayMs(uint32_t delayMs) override;
};

}