#pragma once

#include "SpiInterface.h"

extern "C" void Spi1_MspInit(void);

namespace coffeescales::halwrapper
{

class Spi final : public SpiInterface
{
public:
    void Init() override;
    bool Transmit(const uint8_t *data, uint16_t size) override;
    bool Receive(uint8_t *data, uint16_t size) override;
    void SetChipSelect(GpioPinState state) override;
};

}
