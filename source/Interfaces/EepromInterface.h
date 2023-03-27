#pragma once

#include <cstdint>
#include <cstddef>

namespace coffeescales::drivers
{

class EepromInterface
{
public:
    ~EepromInterface() = default;

    struct StatusRegister
    {
        bool WriteInProcess = false;
        bool WriteEnable = false;
        bool BlockProtection0 = false;
        bool BlockProtection1 = false;
    };

    virtual bool ReadStatusRegister(StatusRegister &status) = 0;
    virtual bool Write(uint16_t address, const uint8_t *data, size_t size) = 0;
    virtual bool Read(uint16_t address, uint8_t *data, size_t size) = 0;
};

}