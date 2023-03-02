#pragma once
#include <cstddef>
#include <cstdint>

namespace halwrapper
{

class UartInterface
{
public:
    ~UartInterface() = default;
    virtual void Transmit(const uint8_t* txData, size_t size) const = 0;
};

}