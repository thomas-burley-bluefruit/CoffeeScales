#include "gtest/gtest.h"

#include "ButtonDriverSpy.h"
#include "PourRate.h"
#include "PourRateUpdateCallbackSpy.h"
#include "ScalesSpy.h"
#include "TimeSpy.h"

#include <vector>

using namespace ::coffeescales::weight;
using namespace ::coffeescales;

class PourRateTests : public testing::Test
{
  public:
    PourRateTests() :
        mPourRate(mScales, mTime, mButtonDriver)
    {
    }

    ScalesSpy mScales;
    halwrapper::TimeSpy mTime;
    drivers::ButtonDriverSpy mButtonDriver;
    PourRate mPourRate;

    float ApplyFilter(float previousValue, float newValue)
    {
        return PourRate::FilterTimeConstant * static_cast<float>(previousValue)
            + (1.0f - PourRate::FilterTimeConstant) * newValue;
    }
};

TEST_F(PourRateTests, registers_with_scales_on_construction)
{
    ASSERT_TRUE(mScales.RegisterCallbackCalled);
    ASSERT_EQ(&mPourRate, mScales.RegisteredCallback);
}

TEST_F(PourRateTests, registers_with_tare_button_on_construction)
{
    ASSERT_TRUE(mButtonDriver.RegisterCallbackCalled);
    ASSERT_EQ(&mPourRate, mButtonDriver.Callback);
}

TEST_F(PourRateTests, registered_callback_is_called_after_weight_reading_received)
{
    // Given
    PourRateUpdateCallbackSpy callback;
    mPourRate.RegisterCallback(&callback);

    // When
    mPourRate.NewWeightReadingMg(1000);

    // Then
    ASSERT_TRUE(callback.PourRateUpdateCalled);
}

TEST_F(PourRateTests, pour_rate_is_calculated_correctly_after_first_two_weight_readings)
{
    // Given
    PourRateUpdateCallbackSpy callback;
    mPourRate.RegisterCallback(&callback);

    const uint32_t firstReadingTickMs = 100;
    const int32_t firstWeightReadingMg = 0;

    const uint32_t secondReadingTickMs = 200;
    const int32_t secondWeightReadingMg = 1000;

    const float weightDiffGrams = (secondWeightReadingMg - firstWeightReadingMg) / 1000.0f;
    const float timeDifferenceSecs = (secondReadingTickMs - firstReadingTickMs) / 1000.0f;
    const float pourRateGramsPerSec = weightDiffGrams / timeDifferenceSecs;
    const float filteredPourRate = ApplyFilter(0, pourRateGramsPerSec);
    const float pourRateRounded = std::round(filteredPourRate * 10) / 10.0f;

    // When
    mTime.GetTickValue = firstReadingTickMs;
    mPourRate.NewWeightReadingMg(firstWeightReadingMg);
    mTime.GetTickValue = secondReadingTickMs;
    mPourRate.NewWeightReadingMg(secondWeightReadingMg);

    // Then
    ASSERT_EQ(pourRateRounded, callback.GramsPerSecond);
}

TEST_F(PourRateTests, callback_is_not_called_again_if_next_weight_reading_is_unchanged)
{
    // Given
    PourRateUpdateCallbackSpy callback;
    mPourRate.RegisterCallback(&callback);

    mTime.GetTickValue = 500;
    mPourRate.NewWeightReadingMg(0);
    ASSERT_FALSE(callback.PourRateUpdateCalled);

    // When
    mTime.GetTickValue += 500;
    mPourRate.NewWeightReadingMg(0);

    // Then
    ASSERT_FALSE(callback.PourRateUpdateCalled);
}

TEST_F(PourRateTests, pour_rate_is_reported_as_0_when_weight_difference_is_negative)
{
    // Given
    PourRateUpdateCallbackSpy callback;
    mPourRate.RegisterCallback(&callback);

    // When
    mTime.GetTickValue = 500;
    mPourRate.NewWeightReadingMg(1000);
    mTime.GetTickValue = 1000;
    mPourRate.NewWeightReadingMg(2000);
    mTime.GetTickValue = 1500;
    mPourRate.NewWeightReadingMg(1000);

    // Then
    ASSERT_TRUE(callback.PourRateUpdateCalled);
    ASSERT_EQ(0, callback.GramsPerSecond);
}

TEST_F(PourRateTests, weight_increase_to_zero_after_tare_button_press_does_not_cause_pour_rate_spike)
{
    // Given
    PourRateUpdateCallbackSpy callback;
    mPourRate.RegisterCallback(&callback);

    mPourRate.NewWeightReadingMg(-100);

    // When
    mPourRate.OnButtonPress(drivers::buttons::Button::Tare);
    mTime.GetTickValue += 100;
    mPourRate.NewWeightReadingMg(0);

    // Then
    ASSERT_FALSE(callback.PourRateUpdateCalled);
}