#pragma once

#include "PersistentMemoryInterface.h"
#include "SpiInterface.h"

#include <cstdint>
#include <cstddef>

namespace coffeescales::drivers
{

class EepromDriver final : public PersistentMemoryInterface
{
public:
    explicit EepromDriver(halwrapper::SpiInterface &spi);
    bool ReadStatusRegister(StatusRegister &status) const override;
    bool Write(uint16_t address, const uint8_t *data, size_t size) const override;
    bool Read(uint16_t address, uint8_t *data, size_t size) const override;

    static constexpr size_t PageSizeBytes = 16;

    struct Instructions
    {
        static constexpr uint8_t Read = 0b0000'0011;
        static constexpr uint8_t Write = 0b0000'0010;
        static constexpr uint8_t ResetWriteEnable = 0b0000'0100;
        static constexpr uint8_t SetWriteEnable = 0b0000'0110;
        static constexpr uint8_t ReadStatusRegister = 0b0000'0101;
        static constexpr uint8_t WriteStatusRegister = 0b0000'0001;

        static constexpr size_t InstructionSize = 1;
        static constexpr size_t AddressSize = 2;
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
    bool TransmitInstruction(const uint8_t instruction) const;
    void SetChipSelect() const;
    void ResetChipSelect() const;

    halwrapper::SpiInterface &mSpi;
};

}
