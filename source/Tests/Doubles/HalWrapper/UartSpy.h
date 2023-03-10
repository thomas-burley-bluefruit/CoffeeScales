#pragma once

#include "UartInterface.h"

namespace halwrapper
{

class UartSpy : public UartInterface
{
public:
    void Init() override;
    void Transmit(const uint8_t *txData, size_t size) const override;
    void SetCallback(ReceiveInterruptCallbackInterface *callback) const override;

    bool InitCalled = false;

    mutable bool TransmitCalled = false;
    mutable const uint8_t* TxData = nullptr;
    mutable size_t TxSize = 0;

    mutable bool SetCallbackCalled = false;
    mutable ReceiveInterruptCallbackInterface* Callback = nullptr;
};

}