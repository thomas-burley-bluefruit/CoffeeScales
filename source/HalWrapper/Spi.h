#pragma once

#include "SpiInterface.h"

namespace coffeescales::halwrapper
{

class Spi final : public SpiInterface
{
public:
    void Init() override;
    bool Transmit(const uint8_t *data, uint16_t size) override;
    bool Receive(uint8_t *data, uint16_t size) override;
};

}
