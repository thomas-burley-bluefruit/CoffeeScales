#include "gtest/gtest.h"

#include "EepromDriverSpy.h"
#include "ScalesMemoryItem.h"

using namespace ::coffeescales::weight;
using namespace ::coffeescales::drivers;

class ScalesMemoryItemTests : public testing::Test
{
public:
    ScalesMemoryItemTests() : mScalesMemoryItem(mEepromDriver)
    {}

    EepromDriverSpy mEepromDriver;
    ScalesMemoryItem mScalesMemoryItem;
};

TEST_F(ScalesMemoryItemTests, Init_restores_calibration_factor_value_from_memory)
{
    // Given
    const float expectedCalibrationFactor = 1.234f;
    mEepromDriver.SetReadData(reinterpret_cast<const uint8_t *>(&expectedCalibrationFactor),
                              sizeof(expectedCalibrationFactor));

    // When
    mScalesMemoryItem.Init();

    // Then
    ASSERT_TRUE(mEepromDriver.ReadCalled);
    ASSERT_EQ(mEepromDriver.ReadAddress, ScalesMemoryItem::Address);
    ASSERT_EQ(mScalesMemoryItem.GetCalibrationFactor(), expectedCalibrationFactor);
}

TEST_F(ScalesMemoryItemTests, Init_sets_default_if_stored_value_is_zero)
{
// Given
    const uint8_t data[sizeof(float)]{0};
    mEepromDriver.SetReadData(data, sizeof(float));

    // When
    mScalesMemoryItem.Init();

    // Then
    ASSERT_TRUE(mEepromDriver.ReadCalled);
    ASSERT_EQ(mEepromDriver.ReadAddress, ScalesMemoryItem::Address);
    ASSERT_EQ(mScalesMemoryItem.GetCalibrationFactor(), ScalesMemoryItem::DefaultCalibrationFactor);
}


TEST_F(ScalesMemoryItemTests, SetCalibrationFactor_updates_stored_calibration_factor)
{
    // Given
    const float expectedCalibrationFactor = 2.456f;
    const auto expectedWriteData = reinterpret_cast<const uint8_t *>(&expectedCalibrationFactor);

    // When
    mScalesMemoryItem.SetCalibrationFactor(expectedCalibrationFactor);

    // Then
    ASSERT_TRUE(mEepromDriver.WriteCalled);
    ASSERT_EQ(mEepromDriver.WriteAddress, ScalesMemoryItem::Address);
    ASSERT_TRUE(
            mEepromDriver.WriteDataEquals(expectedWriteData, sizeof(expectedCalibrationFactor)));

    ASSERT_EQ(mScalesMemoryItem.GetCalibrationFactor(), expectedCalibrationFactor);
}