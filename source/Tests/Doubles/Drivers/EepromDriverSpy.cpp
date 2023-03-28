#include "EepromDriverSpy.h"
#include <cstring>

using namespace coffeescales::drivers;

bool EepromDriverSpy::ReadStatusRegister(PersistentMemoryInterface::StatusRegister &status) const
{
    return false;
}

bool EepromDriverSpy::Write(uint16_t address, const uint8_t *data, size_t size) const
{
    WriteCalled = true;

    memcpy(WriteBuffer, data, size);
    mWriteSize = size;

    return true;
}

bool EepromDriverSpy::Read(uint16_t address, uint8_t *data, size_t size) const
{
    ReadCalled = true;

    memcpy(data, ReadBuffer, size);

    return true;
}

bool EepromDriverSpy::WriteDataEquals(const uint8_t *data, size_t size)
{
    if (size != mWriteSize)
        return false;

    return memcmp(data, WriteBuffer, size) == 0;
}

void EepromDriverSpy::SetReadData(const uint8_t *data, size_t size)
{
    if (size > EepromDriver::PageSizeBytes)
        return;

    memcpy(ReadBuffer, data, size);
}