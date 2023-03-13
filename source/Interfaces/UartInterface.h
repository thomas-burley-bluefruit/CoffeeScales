#pragma once

#include "ReceiveInterruptCallbackInterface.h"

#include <cstddef>
#include <cstdint>

namespace coffeescales::halwrapper
{

class UartInterface
{
public:
    ~UartInterface() = default;
    virtual void Init() = 0;
    virtual void Transmit(const uint8_t* txData, size_t size) const = 0;
    virtual void SetCallback(ReceiveInterruptCallbackInterface *callback) const = 0;
};

}