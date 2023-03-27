#pragma once

#include "SpiInterface.h"

#include <cstring>
#include <vector>

namespace coffeescales::halwrapper
{

enum class SpiInterfaceMethod
{
    Init,
    Transmit,
    Receive,
    SetChipSelect
};

struct SpiInterfaceCall
{
    SpiInterfaceMethod method;
    static constexpr size_t TransmitBufferSize = 256;
    uint8_t data[TransmitBufferSize]{0};
    uint16_t size = 0;
    GpioPinState state = GpioPinState::Reset;

    bool operator==(const SpiInterfaceCall &rhs) const
    {
        if (this->method != rhs.method ||
            this->size != rhs.size ||
            this->state != rhs.state)
        {
            return false;
        }
        if (size == 0)
            return true;
        return memcmp(this->data, rhs.data, this->size) == 0;
    }
};

class SpiSpy final : public SpiInterface
{
public:

    void Init() override;
    bool Transmit(const uint8_t *data, uint16_t size) override;
    bool Receive(uint8_t *data, uint16_t size) override;
    void SetChipSelect(GpioPinState state) override;

    bool InitCalled = false;

    bool TransmitCalled = false;
    bool TransmitSuccess = true;
    uint8_t TransmitData = 0;
    uint16_t TransmitSize = 0;

    bool ReceiveCalled = false;
    bool ReceiveSuccess = true;
    uint8_t ReceiveData = 0;
    uint16_t ReceiveSize = 0;

    bool SetChipSelectCalled = false;

    std::vector<SpiInterfaceCall> Calls;
};

}
