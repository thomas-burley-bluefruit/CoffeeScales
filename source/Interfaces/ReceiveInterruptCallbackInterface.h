#pragma once

#include <cstddef>
#include <cstdint>

namespace coffeescales::halwrapper
{

class ReceiveInterruptCallbackInterface
{
public:
    virtual ~ReceiveInterruptCallbackInterface() = default;

    virtual void OnReceiveInterrupt(uint8_t byte) = 0;
    virtual void OnReceiveError() = 0;
};

}
