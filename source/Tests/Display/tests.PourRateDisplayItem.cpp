#include "DisplayManagerSpy.h"
#include "DisplaySpy.h"
#include "PourRateDisplayItem.h"
#include "PourRateSpy.h"
#include "gtest/gtest.h"

using namespace ::coffeescales;

class PourRateDisplayItemTests : public testing::Test
{
  public:
    PourRateDisplayItemTests() :
        mPourRateDisplayItem(mDisplayManager, mDisplay, mPourRate)
    {
    }

    weight::PourRateSpy mPourRate;
    display::DisplayManagerSpy mDisplayManager;
    display::DisplaySpy mDisplay;
    display::PourRateDisplayItem mPourRateDisplayItem;
};

TEST_F(PourRateDisplayItemTests, registers_with_display_manager_on_construction)
{
    ASSERT_TRUE(mDisplayManager.RegisterDisplayItemCalled);
    ASSERT_EQ(mDisplayManager.RegisteredDisplayItem, &mPourRateDisplayItem);
}

TEST_F(PourRateDisplayItemTests, registers_with_pour_rate_on_construction)
{
    ASSERT_TRUE(mPourRate.RegisterCallbackCalled);
    ASSERT_EQ(mPourRate.RegisteredCallback, &mPourRateDisplayItem);
}

TEST_F(PourRateDisplayItemTests, first_update_after_init_draws_zero_pour_rate)
{
    // Given
    const char* expectedText = "0.0g/s";
    mPourRateDisplayItem.Init();

    // When
    bool redrawRequired = false;
    mPourRateDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.TextsDisplayed.back().c_str(), expectedText);
}

TEST_F(PourRateDisplayItemTests, display_cleared_and_new_rate_shown_on_update_after_pour_rate_update)
{
    // Given
    const float pourRate = 123.4;
    const char* expectedText = "123.4g/s";

    // When
    mPourRateDisplayItem.PourRateUpdate(pourRate);
    bool redrawRequired = false;
    mPourRateDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.TextsDisplayed.back().c_str(), expectedText);
    ASSERT_TRUE(mDisplay.ClearAreaCalled);
    ASSERT_EQ(mDisplay.ClearAreaX, display::PourRateDisplayItem::LocationX);
    ASSERT_EQ(mDisplay.ClearAreaY, display::PourRateDisplayItem::LocationY);
    ASSERT_EQ(mDisplay.ClearAreaWidth, display::PourRateDisplayItem::WidthPx);
    ASSERT_EQ(mDisplay.ClearAreaHeight, display::PourRateDisplayItem::HeightPx);
}

TEST_F(PourRateDisplayItemTests, display_not_updated_if_pour_rate_unchanged)
{
    // Given
    const float pourRate = 123.4;
    const char* expectedText = "123.4g/s";

    mPourRateDisplayItem.PourRateUpdate(pourRate);

    bool redrawRequired = false;
    mPourRateDisplayItem.Update(redrawRequired);
    ASSERT_TRUE(redrawRequired);

    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.TextsDisplayed.back().c_str(), expectedText);
    ASSERT_TRUE(mDisplay.ClearAreaCalled);

    mDisplay.DisplayTextBoxCalled = false;

    // When
    mPourRateDisplayItem.PourRateUpdate(pourRate);
    redrawRequired = false;
    mPourRateDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_FALSE(redrawRequired);
    ASSERT_FALSE(mDisplay.DisplayTextBoxCalled);
}

TEST_F(PourRateDisplayItemTests, hysteresis_applied_between_zero_and_one_tenth_gram_per_second)
{
    // Given
    const char* expectedText = "0.0g/s";
    mPourRateDisplayItem.Init();

    bool redrawRequired = false;
    mPourRateDisplayItem.Update(redrawRequired);

    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    mDisplay.DisplayTextBoxCalled = false;
    ASSERT_STREQ(mDisplay.TextsDisplayed.back().c_str(), expectedText);

    // When
    float pourRate = 0.1f;
    mPourRateDisplayItem.PourRateUpdate(pourRate);
    redrawRequired = false;
    mPourRateDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_FALSE(redrawRequired);
    ASSERT_FALSE(mDisplay.DisplayTextBoxCalled);
}