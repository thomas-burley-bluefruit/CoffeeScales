#include "gtest/gtest.h"

#include "BrewTimer.h"
#include "ButtonDriverSpy.h"
#include "SystemMock.h"
#include "TimerIncrementCallbackSpy.h"

using namespace ::coffeescales;
using namespace ::coffeescales::time;

class BrewTimerTestObject : public BrewTimer
{
  public:
    BrewTimerTestObject(halwrapper::SystemInterface& system,
        drivers::ButtonDriverInterface& timerButton) :
        BrewTimer(system, timerButton)
    {
    }

    static constexpr size_t MaxCallbacks = BrewTimer::MaxCallbacks;
    uint32_t& CallbackCount = mCallbackCount;
    std::array<TimerIncrementCallbackInterface*, MaxCallbacks>& Callbacks = mCallbacks;
};

class BrewTimerTests : public testing::Test
{
  public:
    BrewTimerTests() :
        mBrewTimer(mSystem, mTimerButton)
    {
    }

  protected:
    TimerIncrementCallbackSpy mCallback;
    halwrapper::SystemMock mSystem;
    drivers::ButtonDriverSpy mTimerButton;
    BrewTimerTestObject mBrewTimer;

  protected:
    void AssertTimeForTicks(uint32_t ticks, uint32_t expectedMins, uint32_t expectedSecs)
    {
        mBrewTimer.Reset();
        mBrewTimer.Task();
        mBrewTimer.Start();
        mBrewTimer.Task();
        mSystem.SysTick += ticks;
        mBrewTimer.Task();
        ASSERT_EQ(mCallback.LastMinutes, expectedMins);
        ASSERT_EQ(mCallback.LastSeconds, expectedSecs);
    }
};

TEST_F(BrewTimerTests, Init_registers_with_button_driver)
{
    // Given, when
    mBrewTimer.Init();

    // Then
    ASSERT_TRUE(mTimerButton.RegisterCallbackCalled);
    ASSERT_EQ(&mBrewTimer, mTimerButton.Callback);
}

TEST_F(BrewTimerTests, Can_register_callback)
{
    ASSERT_TRUE(mBrewTimer.RegisterCallback(&mCallback));
    ASSERT_EQ(mBrewTimer.CallbackCount, 1);
    ASSERT_EQ(mBrewTimer.Callbacks[0], &mCallback);
}

TEST_F(BrewTimerTests, Can_only_register_up_to_max_callbacks)
{
    // Given, when
    for (size_t i = 0; i < BrewTimerTestObject::MaxCallbacks; ++i)
        ASSERT_TRUE(mBrewTimer.RegisterCallback(&mCallback));

    // Then
    ASSERT_EQ(mBrewTimer.CallbackCount, mBrewTimer.MaxCallbacks);
    ASSERT_FALSE(mBrewTimer.RegisterCallback(&mCallback));
}

TEST_F(BrewTimerTests, Task_calls_callback_1000ms_after_timer_start_with_0_min_1_sec)
{
    // Given
    mBrewTimer.RegisterCallback(&mCallback);
    mBrewTimer.Start();

    for (int i = 0; i < 999; ++i)
    {
        mBrewTimer.Task();
        ASSERT_EQ(0, mCallback.CallCount);
        mSystem.SysTick++;
    }

    // When
    mSystem.SysTick++;
    mBrewTimer.Task();

    // Then
    ASSERT_EQ(1, mCallback.CallCount);
    ASSERT_EQ(0, mCallback.LastMinutes);
    ASSERT_EQ(1, mCallback.LastSeconds);
}

TEST_F(BrewTimerTests, Task_calls_callback_2000ms_after_timer_start_with_0_min_2_sec)
{
    // Given
    mBrewTimer.RegisterCallback(&mCallback);
    mBrewTimer.Start();

    for (int i = 0; i < 1999; ++i)
    {
        mBrewTimer.Task();
        ASSERT_LT(mCallback.CallCount, 2);
        mSystem.SysTick++;
    }

    // When
    mSystem.SysTick++;
    mBrewTimer.Task();

    // Then
    ASSERT_EQ(2, mCallback.CallCount);
    ASSERT_EQ(0, mCallback.LastMinutes);
    ASSERT_EQ(2, mCallback.LastSeconds);
}

TEST_F(BrewTimerTests, Reset_stops_timer)
{
    // Given: timer started, callback fired once
    mBrewTimer.RegisterCallback(&mCallback);
    mBrewTimer.Start();
    mBrewTimer.Task();
    mSystem.SysTick += 1000;
    mBrewTimer.Task();
    ASSERT_EQ(1, mCallback.CallCount);

    // When
    mBrewTimer.Reset();
    mBrewTimer.Task();
    mCallback.CallCount = 0;
    mSystem.SysTick += 1000;
    mBrewTimer.Task();

    // Then
    ASSERT_EQ(0, mCallback.CallCount);
}

TEST_F(BrewTimerTests, Reset_updates_subscribers_with_0_min_0_sec)
{
    // Given
    mBrewTimer.RegisterCallback(&mCallback);
    mBrewTimer.Start();
    mBrewTimer.Task();
    mSystem.SysTick += 1000;
    mBrewTimer.Task();
    ASSERT_EQ(1, mCallback.CallCount);
    ASSERT_EQ(0, mCallback.LastMinutes);
    ASSERT_EQ(1, mCallback.LastSeconds);

    // When
    mBrewTimer.Reset();
    mBrewTimer.Task();

    // Then
    ASSERT_EQ(2, mCallback.CallCount);
    ASSERT_EQ(0, mCallback.LastMinutes);
    ASSERT_EQ(0, mCallback.LastSeconds);
}

TEST_F(BrewTimerTests, Ticks_are_converted_to_time_correctly)
{
    mBrewTimer.RegisterCallback(&mCallback);

    AssertTimeForTicks(60000, 1, 0);
    AssertTimeForTicks(60999, 1, 0);
    AssertTimeForTicks(61000, 1, 1);
    AssertTimeForTicks(59999, 0, 59);
    AssertTimeForTicks(119999, 1, 59);
}

TEST_F(BrewTimerTests, Task_after_timer_button_press_when_stopped_starts_timer)
{
    // Given
    mBrewTimer.RegisterCallback(&mCallback);
    mBrewTimer.OnButtonPress(drivers::buttons::Button::Timer);

    // When
    mBrewTimer.Task();
    mSystem.SysTick += 1000;
    mBrewTimer.Task();

    // Then
    ASSERT_EQ(1, mCallback.CallCount);
    ASSERT_EQ(0, mCallback.LastMinutes);
    ASSERT_EQ(1, mCallback.LastSeconds);
}

TEST_F(BrewTimerTests, Task_after_timer_button_press_when_running_resets_timer)
{
    // Given: timer started, callback fired once
    mBrewTimer.RegisterCallback(&mCallback);

    mBrewTimer.Start();
    mBrewTimer.Task();

    mSystem.SysTick += 1000;
    mBrewTimer.Task();

    ASSERT_EQ(1, mCallback.CallCount);
    mCallback.CallCount = 0;

    // When
    mBrewTimer.OnButtonPress(drivers::buttons::Button::Timer);
    mBrewTimer.Task();

    mSystem.SysTick += 1000;
    mBrewTimer.Task();

    // Then
    ASSERT_EQ(1, mCallback.CallCount);
    ASSERT_EQ(0, mCallback.LastMinutes);
    ASSERT_EQ(0, mCallback.LastSeconds);
}