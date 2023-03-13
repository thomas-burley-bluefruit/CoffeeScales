#pragma once
#include "UartInterface.h"

namespace coffeescales::halwrapper
{

class Uart : public UartInterface
{
public:
    Uart();
    void Init() override;
    void Transmit(const uint8_t* txData, size_t size) const override;
    void SetCallback(ReceiveInterruptCallbackInterface *callback) const override;
};

}
