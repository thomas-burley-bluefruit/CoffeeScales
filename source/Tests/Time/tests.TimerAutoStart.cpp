#include "gtest/gtest.h"

#include "BrewTimerSpy.h"
#include "ButtonDriverSpy.h"
#include "ScalesSpy.h"
#include "TimerAutoStart.h"
#include "TimerAutoStartCallbackSpy.h"

using namespace ::coffeescales;
using namespace ::coffeescales::time;
using namespace ::coffeescales::drivers;

class TimerAutoStartTests : public testing::Test
{
  public:
    TimerAutoStartTests() :
        mTimerAutoStart(mBrewTimer, mScales, mTimerButton)
    {
    }

  protected:
    BrewTimerSpy mBrewTimer;
    weight::ScalesSpy mScales;
    drivers::ButtonDriverSpy mTimerButton;
    TimerAutoStart mTimerAutoStart;

    void SendDoubleClick(buttons::Button button)
    {
        uint32_t tickMs = 0;
        mTimerAutoStart.OnButtonPress(button, tickMs);
        tickMs += TimerAutoStart::DoubleClickWindowMs - 1;
        mTimerAutoStart.OnButtonPress(button, tickMs);
    }
};

TEST_F(TimerAutoStartTests, callback_registered_with_timer_button_on_construction)
{
    ASSERT_TRUE(mTimerButton.RegisterCallbackCalled);
    ASSERT_EQ(&mTimerAutoStart, mTimerButton.Callback);
}

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

TEST_F(TimerAutoStartTests, next_weight_reading_which_exceeds_threshold_without_enable_does_not_call_callback)
{
    // Given
    TimerAutoStartCallbackSpy callback;
    mTimerAutoStart.RegisterCallback(&callback);

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);

    // Then
    ASSERT_FALSE(callback.TimerAutoStartEnabledCalled);
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

TEST_F(TimerAutoStartTests, weight_readings_at_or_under_threshold_do_not_call_callback)
{
    // Given
    mTimerAutoStart.Enable();

    TimerAutoStartCallbackSpy callback;
    mTimerAutoStart.RegisterCallback(&callback);

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg);

    // Then
    ASSERT_FALSE(callback.TimerAutoStartEnabledCalled);
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

TEST_F(TimerAutoStartTests, double_timer_button_press_within_window_enables_auto)
{
    // Given
    uint32_t tickMs = 0;
    mTimerAutoStart.OnButtonPress(drivers::buttons::Button::Timer, tickMs);

    // When
    tickMs += TimerAutoStart::DoubleClickWindowMs - 1;
    mTimerAutoStart.OnButtonPress(drivers::buttons::Button::Timer, tickMs);
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);

    // Then
    ASSERT_TRUE(mBrewTimer.StartCalled);
}

TEST_F(TimerAutoStartTests, double_click_of_wrong_button_does_not_enable_auto)
{
    // Given
    SendDoubleClick(buttons::Button::Tare);

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);

    // Then
    ASSERT_FALSE(mBrewTimer.StartCalled);
}

TEST_F(TimerAutoStartTests, single_click_of_timer_button_does_not_enable_auto)
{
    // Given
    uint32_t tickMs = 0;
    mTimerAutoStart.OnButtonPress(drivers::buttons::Button::Timer, tickMs);

    // When
    mTimerAutoStart.NewWeightReadingMg(TimerAutoStart::ThresholdMg + 1);

    // Then
    ASSERT_FALSE(mBrewTimer.StartCalled);
}

TEST_F(TimerAutoStartTests, enable_resets_brew_timer)
{
    // Given, when
    mTimerAutoStart.Enable();

    // Then
    ASSERT_TRUE(mBrewTimer.ResetCalled);
}