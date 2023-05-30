#include "gtest/gtest.h"

#include "BrewTimerSpy.h"
#include "ScalesSpy.h"
#include "TimerAutoStart.h"
#include "TimerAutoStartCallbackSpy.h"

using namespace ::coffeescales;
using namespace ::coffeescales::time;

class TimerAutoStartTests : public testing::Test
{
  public:
    TimerAutoStartTests() :
        mTimerAutoStart(mBrewTimer, mScales)
    {
    }

  protected:
    BrewTimerSpy mBrewTimer;
    weight::ScalesSpy mScales;
    TimerAutoStart mTimerAutoStart;
};

TEST_F(TimerAutoStartTests, callback_registered_with_scales_on_construction)
{
    ASSERT_TRUE(mScales.RegisterCallbackCalled);
    ASSERT_EQ(mScales.RegisteredCallback, &mTimerAutoStart);
}

TEST_F(TimerAutoStartTests, enable_calls_registered_callback_with_correct_status)
{
    // Given
    TimerAutoStartCallbackSpy callback;
    mTimerAutoStart.RegisterCallback(&callback);

    // When
    mTimerAutoStart.Enable();

    // Then
    ASSERT_TRUE(callback.TimerAutoStartEnabledCalled);
    ASSERT_TRUE(callback.TimerAutoStartEnabledValue);
}

TEST_F(TimerAutoStartTests, next_weight_reading_which_exceeds_threshold_after_enable_starts_brew_timer)
{
    // Given
    mTimerAutoStart.Enable();

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);

    // Then
    ASSERT_TRUE(mBrewTimer.StartCalled);
}

TEST_F(TimerAutoStartTests, brew_timer_is_not_started_if_enable_not_called)
{
    // Given, when
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);

    // Then
    ASSERT_FALSE(mBrewTimer.StartCalled);
}

TEST_F(TimerAutoStartTests, weight_readings_at_or_under_threshold_do_not_start_timer)
{
    // Given
    mTimerAutoStart.Enable();

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg);

    // Then
    ASSERT_FALSE(mBrewTimer.StartCalled);
}

TEST_F(TimerAutoStartTests, subsequent_weight_readings_exceeding_threshold_do_not_start_timer_again_without_enable_being_called)
{
    // Given
    mTimerAutoStart.Enable();
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);
    ASSERT_TRUE(mBrewTimer.StartCalled);
    mBrewTimer.StartCalled = false;

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);

    // Then
    ASSERT_FALSE(mBrewTimer.StartCalled);
}

TEST_F(TimerAutoStartTests, registered_callback_is_called_when_autostart_disables_after_triggering)
{
    // Given
    mTimerAutoStart.Enable();

    TimerAutoStartCallbackSpy callback;
    mTimerAutoStart.RegisterCallback(&callback);

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);
    ASSERT_TRUE(mBrewTimer.StartCalled);

    // Then
    ASSERT_TRUE(callback.TimerAutoStartEnabledCalled);
    ASSERT_FALSE(callback.TimerAutoStartEnabledValue);
}

TEST_F(TimerAutoStartTests, threshold_is_relative_to_last_weight_reading_before_enable)
{
    // Given
    const uint32_t startingWeight = 1234;
    mTimerAutoStart.NewWeightReadingMg(startingWeight);
    mTimerAutoStart.Enable();

    // When: weight received just under threshold compared to starting weight
    mTimerAutoStart.NewWeightReadingMg(startingWeight + TimerAutoStart::ThresholdMg - 1);

    // Then: timer not started
    ASSERT_FALSE(mBrewTimer.StartCalled);

    // When: weight recieved over threshold compared to starting weight
    mTimerAutoStart.NewWeightReadingMg(startingWeight + (TimerAutoStart::ThresholdMg + 1));

    // Then
    ASSERT_TRUE(mBrewTimer.StartCalled);
}