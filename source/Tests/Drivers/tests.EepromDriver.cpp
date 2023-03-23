#include "gtest/gtest.h"
#include "EepromDriver.h"
#include "SpiSpy.h"

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;

class EepromDriverTests : public testing::Test
{
public:
    EepromDriverTests() : mEeprom(mSpi)
    {}

    SpiSpy mSpi;
    EepromDriver mEeprom;
};

TEST_F(EepromDriverTests, ReadStatusRegister_transmits_correct_instruction)
{
    // Given, when
    EepromDriver::StatusRegister status;
    mEeprom.ReadStatusRegister(status);

    // Then
    ASSERT_TRUE(mSpi.TransmitCalled);
    ASSERT_EQ(mSpi.TransmitSize, EepromDriver::Instructions::InstructionSize);
    ASSERT_EQ(mSpi.TransmitData, EepromDriver::Instructions::ReadStatusRegister);
}

TEST_F(EepromDriverTests, ReadStatusRegister_reads_one_byte)
{
    // Given, when
    EepromDriver::StatusRegister status;
    mEeprom.ReadStatusRegister(status);

    // Then
    ASSERT_TRUE(mSpi.ReceiveCalled);
    ASSERT_EQ(mSpi.ReceiveSize, EepromDriver::Instructions::StatusRegisterSize);
}

TEST_F(EepromDriverTests, ReadStatusRegister_returns_correct_status)
{
    // Given
    uint8_t statusByte = EepromDriver::StatusRegisterMask::WriteInProcess |
                         EepromDriver::StatusRegisterMask::BlockProtection0;
    mSpi.ReceiveData = statusByte;

    // When
    EepromDriver::StatusRegister status;
    mEeprom.ReadStatusRegister(status);

    // Then
    ASSERT_TRUE(status.WriteInProcess);
    ASSERT_TRUE(status.BlockProtection0);
    ASSERT_FALSE(status.WriteEnable);
    ASSERT_FALSE(status.BlockProtection1);
}

TEST_F(EepromDriverTests, ReadStatusRegister_returns_true_when_tx_and_rx_succeed)
{
    EepromDriver::StatusRegister status;
    ASSERT_TRUE(mEeprom.ReadStatusRegister(status));
}

TEST_F(EepromDriverTests, ReadStatusRegister_returns_false_when_tx_or_rx_fail)
{
    EepromDriver::StatusRegister status;

    // Given
    mSpi.TransmitSuccess = false;

    // When, then
    ASSERT_FALSE(mEeprom.ReadStatusRegister(status));

    // Given
    mSpi.TransmitSuccess = true;
    mSpi.ReceiveSuccess = false;

    // When, then
    ASSERT_FALSE(mEeprom.ReadStatusRegister(status));

    // Given
    mSpi.TransmitSuccess = false;
    mSpi.ReceiveSuccess = false;

    // When, then
    ASSERT_FALSE(mEeprom.ReadStatusRegister(status));
}
