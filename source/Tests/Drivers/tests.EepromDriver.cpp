#include "gtest/gtest.h"
#include "EepromDriver.h"
#include "SpiSpy.h"

#include <vector>

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;
using std::vector;

class EepromDriverTests : public testing::Test
{
public:
    EepromDriverTests() : mEeprom(mSpi)
    {}

    void AssertCallsMatch(vector<SpiInterfaceCall> &lhs, vector<SpiInterfaceCall> &rhs)
    {
        ASSERT_EQ(lhs.size(), rhs.size());

        auto expectedCallsIt = lhs.begin();
        for (auto &call: rhs)
            ASSERT_EQ(*expectedCallsIt++, call);
    }

    SpiInterfaceCall GenerateInstructionCall(uint8_t instruction)
    {
        SpiInterfaceCall call{.method = SpiInterfaceMethod::Transmit, .size = EepromDriver::Instructions::InstructionSize};
        memcpy(call.data, &instruction, call.size);
        return call;
    }

    SpiInterfaceCall GenerateWriteDataCall(const uint8_t *data, uint16_t size)
    {
        SpiInterfaceCall call{.method = SpiInterfaceMethod::Transmit, .size = size};
        memcpy(call.data, data, size);
        return call;
    }

    SpiInterfaceCall GenerateReadDataCall(uint16_t size)
    {
        SpiInterfaceCall call{.method = SpiInterfaceMethod::Receive, .size = size};
        return call;
    }

    SpiSpy mSpi;
    EepromDriver mEeprom;

    const SpiInterfaceCall SetChipSelectCall{.method = SpiInterfaceMethod::SetChipSelect, .state = GpioPinState::Set};
    const SpiInterfaceCall ResetChipSelectCall{.method = SpiInterfaceMethod::SetChipSelect, .state = GpioPinState::Reset};
};

TEST_F(EepromDriverTests, Write_sequence)
{
    // Given
    uint16_t address = 0x0001;
    uint8_t addressData[EepromDriver::Instructions::AddressSize];
    addressData[0] = address >> 8;
    addressData[1] = address & 0xFF;

    const size_t dataSize = 1;
    const uint8_t data = 0xAB;

    vector<SpiInterfaceCall> expectedCalls =
            {
                    ResetChipSelectCall,
                    GenerateInstructionCall(EepromDriver::Instructions::SetWriteEnable),
                    SetChipSelectCall,
                    ResetChipSelectCall,
                    GenerateInstructionCall(EepromDriver::Instructions::Write),
                    GenerateWriteDataCall(addressData, EepromDriver::Instructions::AddressSize),
                    GenerateWriteDataCall(&data, dataSize),
                    SetChipSelectCall
            };

    // When
    mEeprom.Write(address, &data, dataSize);

    // Then
    AssertCallsMatch(expectedCalls, mSpi.Calls);
}

TEST_F(EepromDriverTests, Read_sequence)
{
    // Given
    uint16_t address = 0x0123;
    uint8_t addressData[EepromDriver::Instructions::AddressSize];
    addressData[0] = address >> 8;
    addressData[1] = address & 0xFF;

    const uint16_t expectedDataSize = 2;

    vector<SpiInterfaceCall> expectedCalls =
            {
                    ResetChipSelectCall,
                    GenerateInstructionCall(EepromDriver::Instructions::Read),
                    GenerateWriteDataCall(addressData, EepromDriver::Instructions::AddressSize),
                    GenerateReadDataCall(expectedDataSize),
                    SetChipSelectCall
            };

    // When
    uint8_t data[expectedDataSize]{0};
    mEeprom.Read(address, data, expectedDataSize);

    // Then
    AssertCallsMatch(expectedCalls, mSpi.Calls);
}

TEST_F(EepromDriverTests, Read_returns_data_read_from_spi)
{
    // Given
    const uint8_t expectedData = 0xCD;
    const size_t dataSize = 1;
    mSpi.ReceiveData = expectedData;

    // When
    uint8_t actualData = 0;
    mEeprom.Read(0, &actualData, dataSize);

    // Then
    ASSERT_EQ(expectedData, actualData);
}

TEST_F(EepromDriverTests, Can_write_a_full_page)
{
    // Given
    uint8_t data[EepromDriver::PageSizeBytes]{0};

    // When,then
    ASSERT_TRUE(mEeprom.Write(0x0000, data, EepromDriver::PageSizeBytes));
}

TEST_F(EepromDriverTests, Cant_write_more_than_size_of_one_page)
{
    // Given
    uint8_t data[EepromDriver::PageSizeBytes + 1]{0};

    // When,then
    EXPECT_DEATH(mEeprom.Write(0x0000, data, EepromDriver::PageSizeBytes + 1), "");
}

TEST_F(EepromDriverTests, Cant_write_past_first_page_boundary)
{
    // Given
    const size_t dataSize = 5;
    uint8_t data[dataSize]{0};

    // When,then
    EXPECT_DEATH(mEeprom.Write((EepromDriver::PageSizeBytes - dataSize) + 1, data, dataSize), "");
}
