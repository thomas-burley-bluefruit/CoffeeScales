#include <cassert>
#include "EepromDriver.h"

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;

EepromDriver::EepromDriver(halwrapper::SpiInterface &spi) : mSpi(spi)
{}

bool EepromDriver::ReadStatusRegister(StatusRegister &status)
{
    ResetChipSelect();

    if (!TransmitInstruction(Instructions::ReadStatusRegister))
        return false;

    uint8_t rxData = 0;
    if (!mSpi.Receive(&rxData, Instructions::StatusRegisterSize))
        return false;

    SetChipSelect();

    status.WriteInProcess = rxData & StatusRegisterMask::WriteInProcess;
    status.WriteEnable = rxData & StatusRegisterMask::WriteEnable;
    status.BlockProtection0 = rxData & StatusRegisterMask::BlockProtection0;
    status.BlockProtection1 = rxData & StatusRegisterMask::BlockProtection1;

    return true;
}

bool EepromDriver::Write(uint16_t address, const uint8_t *data, size_t size)
{
    assert((address + size) <= PageSizeBytes); // Restrict to first page until more space needed

    ResetChipSelect();

    if (!TransmitInstruction(Instructions::SetWriteEnable))
        return false;

    SetChipSelect();
    ResetChipSelect();

    if (!TransmitInstruction(Instructions::Write))
        return false;

    uint8_t addressData[Instructions::AddressSize];
    addressData[0] = address >> 8;
    addressData[1] = address & 0xFF;

    if (!mSpi.Transmit(addressData, Instructions::AddressSize))
        return false;

    if (!mSpi.Transmit(data, size))
        return false;

    SetChipSelect();

    return true;
}

bool EepromDriver::Read(uint16_t address, uint8_t *data, size_t size)
{
    ResetChipSelect();

    if (!TransmitInstruction(Instructions::Read))
        return false;

    uint8_t addressData[Instructions::AddressSize];
    addressData[0] = address >> 8;
    addressData[1] = address & 0xFF;

    if (!mSpi.Transmit(addressData, Instructions::AddressSize))
        return false;

    if (!mSpi.Receive(data, size))
        return false;

    SetChipSelect();

    return true;
}

bool EepromDriver::TransmitInstruction(const uint8_t instruction) const
{
    return mSpi.Transmit(&instruction, Instructions::InstructionSize);
}

void EepromDriver::SetChipSelect() const
{
    mSpi.SetChipSelect(GpioPinState::Set);
}

void EepromDriver::ResetChipSelect() const
{
    mSpi.SetChipSelect(GpioPinState::Reset);
}
