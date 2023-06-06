#include "gtest/gtest.h"

#include "PourRate.h"
#include "PourRateUpdateCallbackSpy.h"
#include "ScalesSpy.h"
#include "TimeSpy.h"

using namespace ::coffeescales::weight;
using namespace ::coffeescales;

class PourRateTests : public testing::Test
{
  public:
    PourRateTests() :
        mPourRate(mScales, mTime)
    {
    }

    ScalesSpy mScales;
    halwrapper::TimeSpy mTime;
    PourRate mPourRate;
};

TEST_F(PourRateTests, registers_with_scales_on_construction)
{
    ASSERT_TRUE(mScales.RegisterCallbackCalled);
    ASSERT_EQ(&mPourRate, mScales.RegisteredCallback);
}

TEST_F(PourRateTests, registered_callback_is_called_after_second_weight_reading_received)
{
    // Given
    PourRateUpdateCallbackSpy callback;
    mPourRate.RegisterCallback(&callback);

    // When
    mTime.GetTickValue = 500;
    mPourRate.NewWeightReadingMg(0);
    ASSERT_FALSE(callback.PourRateUpdateCalled);
    mTime.GetTickValue = 1000;
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
    const uint32_t pourRateGramsPerSec =
        static_cast<uint32_t>(roundf(weightDiffGrams / timeDifferenceSecs));

    // When
    mTime.GetTickValue = firstReadingTickMs;
    mPourRate.NewWeightReadingMg(firstWeightReadingMg);
    mTime.GetTickValue = secondReadingTickMs;
    mPourRate.NewWeightReadingMg(secondWeightReadingMg);

    // Then
    ASSERT_EQ(pourRateGramsPerSec, callback.GramsPerSecond);
}

TEST_F(PourRateTests, callback_is_not_called_again_if_next_weight_reading_is_unchanged)
{
    // Given
    PourRateUpdateCallbackSpy callback;
    mPourRate.RegisterCallback(&callback);

    mTime.GetTickValue = 500;
    mPourRate.NewWeightReadingMg(0);
    ASSERT_FALSE(callback.PourRateUpdateCalled);
    mTime.GetTickValue += 500;
    mPourRate.NewWeightReadingMg(1000);

    ASSERT_TRUE(callback.PourRateUpdateCalled);
    callback.PourRateUpdateCalled = false;

    // When
    mTime.GetTickValue += 500;
    mPourRate.NewWeightReadingMg(2000);

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