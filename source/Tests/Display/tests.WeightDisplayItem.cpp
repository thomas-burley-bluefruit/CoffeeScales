#include "DisplayManagerSpy.h"
#include "DisplaySpy.h"
#include "ScalesSpy.h"
#include "TerminalSpy.h"
#include "WeightDisplayItem.h"
#include "gtest/gtest.h"

using namespace ::coffeescales;

class WeightDisplayItemTests : public testing::Test
{
  public:
    WeightDisplayItemTests() :
        mWeightDisplayItem(mDisplayManager, mDisplay, mScales, mTerminal)
    {
    }

    void AssertTextForWeight(const char* text, const int32_t weightReadingMg)
    {
        mWeightDisplayItem.NewWeightReadingMg(0);
        mWeightDisplayItem.NewWeightReadingMg(weightReadingMg);
        bool redrawRequired = false;
        mWeightDisplayItem.Update(redrawRequired);
        ASSERT_TRUE(redrawRequired) << "Weight: " << weightReadingMg;
        ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
        ASSERT_STREQ(mDisplay.StringBuffer, text);
        ASSERT_TRUE(mDisplay.ClearAreaCalled);
    }

    weight::ScalesSpy mScales;
    display::DisplayManagerSpy mDisplayManager;
    display::DisplaySpy mDisplay;
    terminal::TerminalSpy mTerminal;
    display::WeightDisplayItem mWeightDisplayItem;
};

TEST_F(WeightDisplayItemTests, registers_with_display_manager_on_construction)
{
    ASSERT_TRUE(mDisplayManager.RegisterDisplayItemCalled);
    ASSERT_EQ(mDisplayManager.RegisteredDisplayItem, &mWeightDisplayItem);
}

TEST_F(WeightDisplayItemTests, init_registers_callback_with_scales)
{
    // Given, when
    mWeightDisplayItem.Init();

    // Then
    ASSERT_TRUE(mScales.RegisterCallbackCalled);
    ASSERT_EQ(mScales.RegisteredCallback, &mWeightDisplayItem);
}

TEST_F(WeightDisplayItemTests, first_update_after_init_draws_zero_grams)
{
    // Given
    const char* expectedText = "0.0g";
    mWeightDisplayItem.Init();

    // When
    bool redrawRequired = false;
    mWeightDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
}

TEST_F(WeightDisplayItemTests, display_cleared_and_new_weight_shown_on_update_after_weight_reading)
{
    // Given
    const int32_t weightReading = 1234;
    const char* expectedText = "1.2g";

    // When
    mWeightDisplayItem.NewWeightReadingMg(weightReading);
    bool redrawRequired = false;
    mWeightDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
    ASSERT_TRUE(mDisplay.ClearAreaCalled);
    ASSERT_EQ(mDisplay.ClearAreaX, display::WeightDisplayItem::LocationX);
    ASSERT_EQ(mDisplay.ClearAreaY, display::WeightDisplayItem::LocationY);
    ASSERT_EQ(mDisplay.ClearAreaWidth, display::WeightDisplayItem::WidthPx);
    ASSERT_EQ(mDisplay.ClearAreaHeight, display::WeightDisplayItem::HeightPx);
}

TEST_F(WeightDisplayItemTests, negative_weights_displayed_correctly)
{
    // Given
    const int32_t weightReading = -1234;
    const char* expectedText = "-1.2g";

    // When
    mWeightDisplayItem.NewWeightReadingMg(weightReading);
    bool redrawRequired = false;
    mWeightDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(redrawRequired);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
    ASSERT_TRUE(mDisplay.ClearAreaCalled);
}

TEST_F(WeightDisplayItemTests, display_not_updated_if_weight_unchanged)
{
    // Given
    const int32_t weightReading = 1234;
    const char* expectedText = "1.2g";

    mWeightDisplayItem.NewWeightReadingMg(weightReading);

    bool redrawRequired = false;
    mWeightDisplayItem.Update(redrawRequired);
    ASSERT_TRUE(redrawRequired);

    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
    ASSERT_TRUE(mDisplay.ClearAreaCalled);

    mDisplay.DisplayTextBoxCalled = false;

    // When
    mWeightDisplayItem.NewWeightReadingMg(weightReading);
    redrawRequired = false;
    mWeightDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_FALSE(redrawRequired);
    ASSERT_FALSE(mDisplay.DisplayTextBoxCalled);
}

TEST_F(WeightDisplayItemTests, weight_is_rounded_correctly)
{
    AssertTextForWeight("1.1g", 1099);
    AssertTextForWeight("1.1g", 1051);
    AssertTextForWeight("1.0g", 1049);
    AssertTextForWeight("1.0g", 999);
    AssertTextForWeight("0.9g", 944);
    AssertTextForWeight("0.1g", 99);
    AssertTextForWeight("-1.0g", -999);
    AssertTextForWeight("-1.1g", -1050);
    AssertTextForWeight("100.0g", 99950);
    AssertTextForWeight("15.9g", 15943);
}

TEST_F(WeightDisplayItemTests, weight_is_printed_to_terminal_when_debug_print_turned_on)
{
    // Given
    int32_t weightReading = 1000;
    mWeightDisplayItem.NewWeightReadingMg(weightReading);
    bool redrawRequired = false;
    mWeightDisplayItem.Update(redrawRequired);
    ASSERT_FALSE(mTerminal.TextOutCalled);

    // When
    weightReading = 1200;
    const char* expectedText = "1.2g\n";
    mWeightDisplayItem.DebugPrint(true);
    mWeightDisplayItem.NewWeightReadingMg(weightReading);
    mWeightDisplayItem.Update(redrawRequired);

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(mTerminal.TextOutValue, expectedText);
}