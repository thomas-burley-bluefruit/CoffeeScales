#include "UartSpy.h"

using namespace ::coffeescales::halwrapper;

void UartSpy::Init()
{
    InitCalled = true;
}

void UartSpy::Transmit(const uint8_t *txData, size_t size) const
{
    TransmitCalled = true;
    TxData = txData;
    TxSize = size;
}

void UartSpy::SetCallback(ReceiveInterruptCallbackInterface *callback) const
{
    SetCallbackCalled = true;
    Callback = callback;
}

