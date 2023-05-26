#include "BrewTimerSpy.h"
#include "DisplayManagerSpy.h"
#include "DisplaySpy.h"
#include "TimeDisplayItem.h"
#include "gtest/gtest.h"

using namespace ::coffeescales;

class TimeDisplayItemTests : public testing::Test
{
  public:
    TimeDisplayItemTests() :
        mTimeDisplayItem(mDisplayManager, mDisplay, mBrewTimer)
    {
    }

    void AssertFormatForTime(uint32_t minutes, uint32_t seconds, const char* expectedString)
    {
        mTimeDisplayItem.TimeUpdate(minutes, seconds);
        bool redrawRequired = false;
        mTimeDisplayItem.Update(redrawRequired);
        ASSERT_TRUE(redrawRequired);
        ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
        ASSERT_STREQ(mDisplay.StringBuffer, expectedString);
    }

    time::BrewTimerSpy mBrewTimer;
    display::DisplayManagerSpy mDisplayManager;
    display::DisplaySpy mDisplay;
    display::TimeDisplayItem mTimeDisplayItem;
};

TEST_F(TimeDisplayItemTests, init_registers_with_display_manager)
{
    // Given, when
    mTimeDisplayItem.Init();

    // Then
    ASSERT_TRUE(mDisplayManager.RegisterDisplayItemCalled);
    ASSERT_EQ(mDisplayManager.RegisteredDisplayItem, &mTimeDisplayItem);
}

TEST_F(TimeDisplayItemTests, init_registers_callback_with_brew_timer)
{
    // Given, when
    mTimeDisplayItem.Init();

    // Then
    ASSERT_TRUE(mBrewTimer.RegisterCallbackCalled);
    ASSERT_EQ(mBrewTimer.RegisteredCallback, &mTimeDisplayItem);
}

TEST_F(TimeDisplayItemTests, update_after_init_draws_zeroed_timer)
{
    // Given
    const char* expectedText = "0:00";
    mTimeDisplayItem.Init();

    // When
    bool redrawRequired = false;
    mTimeDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
}

TEST_F(TimeDisplayItemTests, display_cleared_and_new_time_shown_on_update_after_time_update)
{
    // Given
    const uint32_t minutes = 1;
    const uint32_t seconds = 23;
    const char* expectedText = "1:23";

    // When
    mTimeDisplayItem.TimeUpdate(minutes, seconds);
    bool redrawRequired = false;
    mTimeDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
    ASSERT_TRUE(mDisplay.ClearAreaCalled);
    ASSERT_EQ(mDisplay.ClearAreaX, mTimeDisplayItem.LocationX);
    ASSERT_EQ(mDisplay.ClearAreaY, mTimeDisplayItem.LocationY);
    ASSERT_EQ(mDisplay.ClearAreaWidth, mTimeDisplayItem.WidthPx);
    ASSERT_EQ(mDisplay.ClearAreaHeight, mTimeDisplayItem.HeightPx);
}

TEST_F(TimeDisplayItemTests, Time_is_formatted_correctly)
{
    AssertFormatForTime(0, 1, "0:01");
    AssertFormatForTime(1, 1, "1:01");
    AssertFormatForTime(1, 0, "1:00");
    AssertFormatForTime(10, 1, "10:01");
}
