#include "gtest/gtest.h"
#include "ButtonDriver.h"
#include "ButtonGpioSpy.h"
#include "ButtonPressCallbackSpy.h"
#include "SystemMock.h"

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;
using ::std::vector;

class ButtonDriverTests : public testing::Test
{
public:
    ButtonDriverTests() : mButtonDriver(mButton, mButtonGpio, mSystem)
    {}

protected:
    static constexpr buttons::Button mButton = buttons::Button::Tare;
    ButtonGpioSpy mButtonGpio;
    SystemMock mSystem;
    ButtonDriver mButtonDriver;
};

TEST_F(ButtonDriverTests, Init_registers_callback_with_gpio)
{
    // Given
    ASSERT_FALSE(mButtonGpio.RegisterCallbackCalled);

    // When
    mButtonDriver.Init();

    // Then
    ASSERT_TRUE(mButtonGpio.RegisterCallbackCalled);
    ASSERT_EQ(&mButtonDriver, mButtonGpio.Callback);
}

TEST_F(ButtonDriverTests,
       Registered_callback_is_called_on_external_interrupt_with_correct_button_argument)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);

    mSystem.SysTick = buttons::MinimumIntervalMs(mButton);

    // When
    mButtonDriver.OnExternalInterrupt();

    // Then
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);
    ASSERT_EQ(mButton, callbackSpy.Button);
}

TEST_F(ButtonDriverTests, Button_is_debounced)
{
    // Given
    ButtonPressCallbackSpy callbackSpy;
    mButtonDriver.RegisterCallback(&callbackSpy);

    const auto minimumIntervalMs = buttons::MinimumIntervalMs(mButton);
    mSystem.SysTick = minimumIntervalMs;

    mButtonDriver.OnExternalInterrupt();
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);

    // When
    const auto debouncePeriod = mSystem.SysTick + minimumIntervalMs;
    while (mSystem.SysTick++ < debouncePeriod - 1)
    {
        callbackSpy.Reset();
        mButtonDriver.OnExternalInterrupt();
        ASSERT_FALSE(callbackSpy.OnButtonPressCalled);
    }

    // Then
    mButtonDriver.OnExternalInterrupt();
    ASSERT_TRUE(callbackSpy.OnButtonPressCalled);
}
