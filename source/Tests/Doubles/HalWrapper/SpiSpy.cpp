#include "SpiSpy.h"

using namespace ::coffeescales::halwrapper;


void SpiSpy::Init()
{
    Calls.push_back({SpiInterfaceMethod::Init});
    InitCalled = true;
}

bool SpiSpy::Transmit(const uint8_t *data, uint16_t size)
{
    SpiInterfaceCall call;
    call.method = SpiInterfaceMethod::Transmit;
    call.size = size;
    memcpy(call.data, data, size);

    Calls.push_back(call);

    TransmitCalled = true;
    TransmitData = *data;
    TransmitSize = size;
    return TransmitSuccess;
}

bool SpiSpy::Receive(uint8_t *data, uint16_t size)
{
    Calls.push_back({.method = SpiInterfaceMethod::Receive, .size = size});

    ReceiveCalled = true;
    *data = ReceiveData;
    ReceiveSize = size;
    return ReceiveSuccess;
}

void SpiSpy::SetChipSelect(GpioPinState state)
{
    Calls.push_back({.method = SpiInterfaceMethod::SetChipSelect, .state = state});

    SetChipSelectCalled = true;
}
