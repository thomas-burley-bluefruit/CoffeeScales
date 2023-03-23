#include "EepromDriver.h"

using namespace ::coffeescales::drivers;

EepromDriver::EepromDriver(halwrapper::SpiInterface &spi) : mSpi(spi)
{}

bool EepromDriver::ReadStatusRegister(StatusRegister &status)
{
    if (!mSpi.Transmit(&Instructions::ReadStatusRegister, Instructions::InstructionSize))
        return false;

    uint8_t rxData = 0;
    if (!mSpi.Receive(&rxData, Instructions::StatusRegisterSize))
        return false;

    status.WriteInProcess = rxData & StatusRegisterMask::WriteInProcess;
    status.WriteEnable = rxData & StatusRegisterMask::WriteEnable;
    status.BlockProtection0 = rxData & StatusRegisterMask::BlockProtection0;
    status.BlockProtection1 = rxData & StatusRegisterMask::BlockProtection1;

    return true;
}
