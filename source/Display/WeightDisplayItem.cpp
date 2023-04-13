#include "WeightDisplayItem.h"

#include <cmath>
#include <cstring>

using namespace ::coffeescales::display;

WeightDisplayItem::WeightDisplayItem(coffeescales::display::DisplayInterface &display,
                                     weight::ScalesInterface &scales,
                                     terminal::TerminalInterface &terminal) :
        mDisplay(display),
        mScales(scales),
        mTerminal(terminal)
{}

void WeightDisplayItem::Init()
{
    DisplayWeightString("0.0g");
    mScales.RegisterCallback(this);
}

void WeightDisplayItem::NewWeightReadingMg(int32_t weightMg)
{
    bool negativeWeight = weightMg < 0;
    int32_t absWeight = abs(weightMg);

    auto grams = static_cast<float>(absWeight) / 1000.0f;
    auto deciGrams = static_cast<int32_t>(roundf(grams * 10.0f));
    float roundedGrams = static_cast<float>(deciGrams) / 10;
    int32_t integerGrams = floor(roundedGrams);
    auto tenthGrams = static_cast<int32_t>((roundedGrams - static_cast<float>(integerGrams)) *
                                           10.0f);

    if (negativeWeight)
        integerGrams = -integerGrams;

    if (mLastGramsDisplayed == integerGrams && mLastDeciGramsDisplayed == tenthGrams)
        return;

    mLastGramsDisplayed = integerGrams;
    mLastDeciGramsDisplayed = tenthGrams;

    snprintf(mPrintBuffer, PrintBufferSize, "%li.%lig", mLastGramsDisplayed,
             mLastDeciGramsDisplayed);

    DisplayWeightString(mPrintBuffer);
}

void WeightDisplayItem::DisplayWeightString(const char *string)
{
    mDisplay.ClearDisplay();
    mDisplay.DisplayTextBox(0, 0, mDisplay.DisplayWidth(), mDisplay.DisplayHeight(), string,
                            Justify::Center);

    if (mDebugPrintWeight)
    {
        strncat(mPrintBuffer, "\n", PrintBufferSize);
        mTerminal.TextOut(mPrintBuffer);
    }
}

void WeightDisplayItem::DebugPrint(bool on)
{
    mDebugPrintWeight = on;
}
