#pragma once

#include "EepromInterface.h"
#include "SpiInterface.h"

#include <cstdint>
#include <cstddef>

namespace coffeescales::drivers
{

class EepromDriver final : public EepromInterface
{
public:
    explicit EepromDriver(halwrapper::SpiInterface &spi);
    bool ReadStatusRegister(StatusRegister &status) override;

    struct Instructions
    {
        static constexpr uint8_t Read = 0b0000'0011;
        static constexpr uint8_t Write = 0b0000'0010;
        static constexpr uint8_t ResetWriteEnable = 0b0000'0100;
        static constexpr uint8_t SetWriteEnable = 0b0000'0110;
        static constexpr uint8_t ReadStatusRegister = 0b0000'0101;
        static constexpr uint8_t WriteStatusRegister = 0b0000'0001;

        static constexpr size_t InstructionSize = 1;
        static constexpr size_t StatusRegisterSize = 1;
    };

    struct StatusRegisterMask
    {
        static constexpr uint8_t WriteInProcess = 0b0000'0001;
        static constexpr uint8_t WriteEnable = 0b0000'0010;
        static constexpr uint8_t BlockProtection0 = 0b0000'0100;
        static constexpr uint8_t BlockProtection1 = 0b0000'1000;
    };

private:
    halwrapper::SpiInterface &mSpi;
};

}
