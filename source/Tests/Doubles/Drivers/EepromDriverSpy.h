#pragma once

#include "EepromDriver.h"

namespace coffeescales::drivers
{

class EepromDriverSpy final : public PersistentMemoryInterface
{
public:
    // EepromInterface
    bool Write(uint16_t address, const uint8_t *data, size_t size) const override;
    bool Read(uint16_t address, uint8_t *data, size_t size) const override;

    bool WriteDataEquals(const uint8_t *data, size_t size) const;
    void SetReadData(const uint8_t *data, size_t size);

    mutable bool WriteCalled = false;
    mutable uint16_t WriteAddress = 0;
    mutable uint8_t WriteBuffer[EepromDriver::PageSizeBytes]{0};

    mutable bool ReadCalled = false;
    mutable uint16_t ReadAddress = 0;
    uint8_t ReadBuffer[EepromDriver::PageSizeBytes]{0};

private:
    mutable size_t mWriteSize = 0;
};

}
