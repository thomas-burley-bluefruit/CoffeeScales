#pragma once

#include <cstdint>
#include <cstddef>

namespace coffeescales::drivers
{

class PersistentMemoryInterface
{
public:
    ~PersistentMemoryInterface() = default;

    virtual bool Write(uint16_t address, const uint8_t *data, size_t size) const = 0;
    virtual bool Read(uint16_t address, uint8_t *data, size_t size) const = 0;
};

}