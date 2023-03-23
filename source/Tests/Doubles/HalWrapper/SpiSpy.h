#pragma once

#include "SpiInterface.h"

namespace coffeescales::halwrapper
{

class SpiSpy final : public SpiInterface
{
public:
    void Init() override;
    bool Transmit(const uint8_t *data, uint16_t size) override;
    bool Receive(uint8_t *data, uint16_t size) override;

    bool InitCalled = false;

    bool TransmitCalled = false;
    bool TransmitSuccess = true;
    uint8_t TransmitData = 0;
    uint16_t TransmitSize = 0;

    bool ReceiveCalled = false;
    bool ReceiveSuccess = true;
    uint8_t ReceiveData = 0;
    uint16_t ReceiveSize = 0;;
};

}
