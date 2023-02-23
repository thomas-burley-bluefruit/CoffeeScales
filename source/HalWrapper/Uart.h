#pragma once
#include "UartInterface.h"

namespace halwrapper
{

class Uart : public UartInterface
{
public:
    Uart();
    void Init();
    void Transmit(uint8_t* txData, size_t size) const override;
};

}
