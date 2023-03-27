#pragma once

#include <cstdint>
#include "Types.h"

namespace coffeescales::halwrapper
{

class SpiInterface
{
public:
    ~SpiInterface() = default;
    virtual void Init() = 0;
    virtual bool Transmit(const uint8_t *data, uint16_t size) = 0;
    virtual bool Receive(uint8_t *data, uint16_t size) = 0;
    virtual void SetChipSelect(GpioPinState state) = 0;
};

}
