#pragma once

#include <cstdint>

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
};

}