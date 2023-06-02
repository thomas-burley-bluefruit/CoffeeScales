#include "ButtonDriver.h"
#include "ButtonPressCallbackSpy.h"
#include "ExternalInterruptCallbackRegisterableSpy.h"
#include "GpioSpy.h"
#include "TimeSpy.h"
#include "gtest/gtest.h"

#include <vector>

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;
using ::std::vector;

class ButtonDriverTests : public testing::Test
{
  public:
    ButtonDriverTests() :
        mButtonDriver(mButton, mButtonGpio, mInterruptTimer, mTime)
    {
    }

  protected:
    static constexpr buttons::Button mButton = buttons::Button::Tare;
    GpioSpy mButtonGpio;
    ExternalInterruptCallbackRegisterableSpy mInterruptTimer;
    TimeSpy mTime;
    ButtonDriver mButtonDriver;

    void TriggerButtonPress()
    {
        mButtonGpio.GetPinStateValue = GpioPinState::Reset;
        for (int i = 0; i < ButtonDriver::MinimumOnTimeMs; ++i)
        {
            mButtonDriver.OnExternalInterrupt();
        }
    }

    void ReleaseButton()
    {
        mButtonGpio.GetPinStateValue = GpioPinState::Set;
        mButtonDriver.OnExternalInterrupt();
    }

    void SatisfyDebouncePeriod()
    {
        mTime.GetTickValue += buttons::MinimumIntervalMs(mButton);
        mButtonDriver.OnExternalInterrupt();
    }
};

TEST_F(ButtonDriverTests, Init_registers_callback_with_interrupt_timer)
{
    // Given
    ASSERT_FALSE(mInterruptTimer.RegisterCallbackCalled);

    // When
    mButtonDriver.Init();

    // Then
    ASSERT_TRUE(mInterruptTimer.RegisterCallbackCalled);
    ASSERT_EQ(&mButtonDriver, mInterruptTimer.Callback);
}

TEST_F(ButtonDriverTests,
       Registered_callback_is_called_when_button_gpio_is_reset_for_minimum_counts_required)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);
    mButtonGpio.GetPinStateValue = GpioPinState::Reset;

    // When
    for (int i = 0; i < ButtonDriver::MinimumOnTimeMs - 1; ++i)
    {
        mButtonDriver.OnExternalInterrupt();
        ASSERT_FALSE(callbackSpy.OnButtonPressCalled);
    }

    mButtonDriver.OnExternalInterrupt();

    // Then
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);
    ASSERT_EQ(mButton, callbackSpy.Button);
}

TEST_F(ButtonDriverTests,
       Registered_callback_is_not_called_when_button_gpio_is_set_for_minimum_counts_required)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);
    mButtonGpio.GetPinStateValue = GpioPinState::Set;

    // When, then
    for (int i = 0; i < ButtonDriver::MinimumOnTimeMs; ++i)
    {
        mButtonDriver.OnExternalInterrupt();
        ASSERT_FALSE(callbackSpy.OnButtonPressCalled);
    }
}

TEST_F(ButtonDriverTests,
       On_time_is_reset_when_button_gpio_goes_to_set)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);
    mButtonGpio.GetPinStateValue = GpioPinState::Reset;

    for (int i = 0; i < ButtonDriver::MinimumOnTimeMs - 1; ++i)
    {
        mButtonDriver.OnExternalInterrupt();
        ASSERT_FALSE(callbackSpy.OnButtonPressCalled);
    }

    // When
    mButtonGpio.GetPinStateValue = GpioPinState::Set;
    mButtonDriver.OnExternalInterrupt();
    mButtonGpio.GetPinStateValue = GpioPinState::Reset;
    mButtonDriver.OnExternalInterrupt();

    // Then
    ASSERT_FALSE(callbackSpy.OnButtonPressCalled);
}

TEST_F(ButtonDriverTests, Button_is_debounced)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);

    TriggerButtonPress();
    ReleaseButton();
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);
    callbackSpy.Reset();

    // When
    mButtonGpio.GetPinStateValue = GpioPinState::Reset;
    const auto minimumIntervalMs = buttons::MinimumIntervalMs(mButton);
    for (int i = 0; i < minimumIntervalMs - 1; ++i)
    {
        mTime.GetTickValue++;
        mButtonDriver.OnExternalInterrupt();
        ASSERT_FALSE(callbackSpy.OnButtonPressCalled);
    }

    // Then
    mTime.GetTickValue++;
    mButtonDriver.OnExternalInterrupt();
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);
}

TEST_F(ButtonDriverTests, Button_needs_to_be_released_before_callback_will_fire_again)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);

    TriggerButtonPress();
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);
    callbackSpy.Reset();

    // When
    SatisfyDebouncePeriod();
    TriggerButtonPress();

    // Then
    ASSERT_FALSE(callbackSpy.OnButtonPressCalled);
    callbackSpy.Reset();

    // When
    mButtonGpio.GetPinStateValue = GpioPinState::Set;
    mButtonDriver.OnExternalInterrupt();
    SatisfyDebouncePeriod();
    TriggerButtonPress();

    // Then
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);
}

TEST_F(ButtonDriverTests, SysTick_is_passed_to_callback)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);

    mTime.GetTickValue = 1234;

    // When
    TriggerButtonPress();
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);

    // Then
    ASSERT_EQ(mTime.GetTickValue, callbackSpy.TickMs);
}

TEST_F(ButtonDriverTests, Multiple_callbacks_can_be_registered)
{
    // Given
    std::vector<ButtonPressCallbackSpy> callbacks(ButtonDriver::MaxCallbacks,
        ButtonPressCallbackSpy());

    for (auto& callback : callbacks)
    {
        mButtonDriver.RegisterCallback(&callback);
    }

    // When
    TriggerButtonPress();

    // Then
    for (auto& callback : callbacks)
    {
        ASSERT_TRUE(callback.OnButtonPressCalled);
    }
}

TEST_F(ButtonDriverTests, Can_only_register_max_callbacks)
{
    // Given
    ButtonPressCallbackSpy callback;

    // When
    for (int i = 0; i < ButtonDriver::MaxCallbacks; ++i)
    {
        mButtonDriver.RegisterCallback(&callback);
    }

    // Then
    ASSERT_DEATH(mButtonDriver.RegisterCallback(&callback), "");
}
