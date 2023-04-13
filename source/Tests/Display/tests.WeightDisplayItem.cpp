#include "gtest/gtest.h"
#include "DisplaySpy.h"
#include "ScalesSpy.h"
#include "TerminalSpy.h"
#include "WeightDisplayItem.h"

using namespace ::coffeescales;

class WeightDisplayItemTests : public testing::Test
{
public:
    WeightDisplayItemTests() : mWeightDisplayItem(mDisplay, mScales, mTerminal)
    {}

    void AssertTextForWeight(const char *text, const int32_t weightReadingMg)
    {
        mWeightDisplayItem.NewWeightReadingMg(weightReadingMg);
        ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
        ASSERT_STREQ(mDisplay.StringBuffer, text);
        ASSERT_TRUE(mDisplay.ClearDisplayCalled);
    }

    weight::ScalesSpy mScales;
    display::DisplaySpy mDisplay;
    terminal::TerminalSpy mTerminal;
    display::WeightDisplayItem mWeightDisplayItem;
};

TEST_F(WeightDisplayItemTests, init_registers_callback_with_scales)
{
    // Given, when
    mWeightDisplayItem.Init();

    // Then
    ASSERT_TRUE(mScales.RegisterCallbackCalled);
    ASSERT_EQ(mScales.RegisteredCallback, &mWeightDisplayItem);
}

TEST_F(WeightDisplayItemTests, zero_grams_printed_to_display_on_init_prior_to_first_weight_reading)
{
    // Given
    const char *expectedText = "0.0g";

    // When
    mWeightDisplayItem.Init();

    // Then
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
}

TEST_F(WeightDisplayItemTests, display_cleared_and_new_weight_shown_on_weight_reading)
{
    // Given
    const int32_t weightReading = 1234;
    const char *expectedText = "1.2g";

    // When
    mWeightDisplayItem.NewWeightReadingMg(weightReading);

    // Then
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
    ASSERT_TRUE(mDisplay.ClearDisplayCalled);
}

TEST_F(WeightDisplayItemTests, negative_weights_displayed_correctly)
{
    // Given
    const int32_t weightReading = -1234;
    const char *expectedText = "-1.2g";

    // When
    mWeightDisplayItem.NewWeightReadingMg(weightReading);

    // Then
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
    ASSERT_TRUE(mDisplay.ClearDisplayCalled);
}

TEST_F(WeightDisplayItemTests, display_not_updated_if_weight_unchanged)
{
    // Given
    const int32_t weightReading = 1234;
    const char *expectedText = "1.2g";

    mWeightDisplayItem.NewWeightReadingMg(weightReading);
    ASSERT_TRUE(mDisplay.DisplayTextBoxCalled);
    ASSERT_STREQ(mDisplay.StringBuffer, expectedText);
    ASSERT_TRUE(mDisplay.ClearDisplayCalled);

    mDisplay.DisplayTextBoxCalled = false;

    // When
    mWeightDisplayItem.NewWeightReadingMg(weightReading);

    // Then
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
}

TEST_F(WeightDisplayItemTests, weight_is_printed_to_terminal_when_debug_print_turned_on)
{
    // Given
    int32_t weightReading = 1000;
    mWeightDisplayItem.NewWeightReadingMg(weightReading);
    ASSERT_FALSE(mTerminal.TextOutCalled);

    // When
    weightReading = 1200;
    const char *expectedText = "1.2g\n";
    mWeightDisplayItem.WeightDebugPrint(true);
    mWeightDisplayItem.NewWeightReadingMg(weightReading);

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(mTerminal.TextOutValue, expectedText);
}