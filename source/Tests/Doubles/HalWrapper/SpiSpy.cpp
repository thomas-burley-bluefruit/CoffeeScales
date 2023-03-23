#include "SpiSpy.h"

using namespace ::coffeescales::halwrapper;


void SpiSpy::Init()
{
    InitCalled = true;
}

bool SpiSpy::Transmit(const uint8_t *data, uint16_t size)
{
    TransmitCalled = true;
    TransmitData = *data;
    TransmitSize = size;
    return TransmitSuccess;
}

bool SpiSpy::Receive(uint8_t *data, uint16_t size)
{
    ReceiveCalled = true;
    *data = ReceiveData;
    ReceiveSize = size;
    return ReceiveSuccess;
}
