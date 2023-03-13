#pragma once

#include <cstddef>
#include <cstdint>

namespace coffeescales::halwrapper
{

class ReceiveInterruptCallbackInterface
{
public:
    virtual ~ReceiveInterruptCallbackInterface()
    {}

    virtual void OnReceiveInterrupt(const uint8_t byte) = 0;
    virtual void OnReceiveError() = 0;
};

}
