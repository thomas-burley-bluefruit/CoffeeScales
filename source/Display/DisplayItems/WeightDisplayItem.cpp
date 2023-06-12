#include "WeightDisplayItem.h"

#include <cmath>
#include <cstdio>
#include <cstring>

using namespace ::coffeescales::display;

WeightDisplayItem::WeightDisplayItem(DisplayManagerInterface& displayManager,
    DisplayInterface& display, weight::ScalesInterface& scales,
    terminal::TerminalInterface& terminal) :
    mDisplayManager(displayManager),
    mDisplay(display),
    mScales(scales),
    mTerminal(terminal)
{
    mDisplayManager.RegisterDisplayItem(this);
}

void WeightDisplayItem::Init()
{
    mScales.RegisterCallback(this);
    LoadPrintBuffer();
    mRedrawRequired = true;
}

void WeightDisplayItem::NewWeightReadingMg(int32_t weightMg)
{
    int32_t absWeight = abs(weightMg);
    bool weightRoundsToZeroG = absWeight < 50;

    if (!weightRoundsToZeroG && abs(weightMg - mLastWeightDisplayedMg) < HysteresisMg)
    {
        return;
    }

    auto grams = static_cast<float>(absWeight) / 1000.0f;
    auto deciGrams = static_cast<int32_t>(roundf(grams * 10.0f));
    float roundedGrams = (static_cast<float>(deciGrams) / 10) + 0.001;
    int32_t integerGrams = floor(roundedGrams);
    auto tenthGrams =
        static_cast<int32_t>((roundedGrams - static_cast<float>(integerGrams)) * 10.0f);

    bool negativeWeight = weightMg < 0 && !(integerGrams == 0 && tenthGrams == 0);

    if (mLastGramsDisplayed == integerGrams && mLastDeciGramsDisplayed == tenthGrams
        && mLastWeightDisplayedWasNegative == negativeWeight)
    {
        return;
    }

    mLastWeightDisplayedMg = weightMg;
    mLastGramsDisplayed = integerGrams;
    mLastDeciGramsDisplayed = tenthGrams;
    mLastWeightDisplayedWasNegative = negativeWeight;

    LoadPrintBuffer();
    mRedrawRequired = true;
}

void WeightDisplayItem::DisplayWeightString(const char* string)
{
    mDisplay.ClearArea(LocationX, LocationY, WidthPx, HeightPx);
    mDisplay.DisplayTextBox(LocationX, LocationY, WidthPx, HeightPx, string, Justify::Right,
        FontSize::Large);

    if (mDebugPrintWeight)
    {
        strncat(mPrintBuffer, "\n", PrintBufferSize);
        mTerminal.TextOut(mPrintBuffer);
    }
}

void WeightDisplayItem::LoadPrintBuffer()
{
    snprintf(mPrintBuffer, PrintBufferSize, "%s%li.%lig",
        mLastWeightDisplayedWasNegative != 0 ? "-" : "", mLastGramsDisplayed,
        mLastDeciGramsDisplayed);
}

void WeightDisplayItem::DebugPrint(bool on)
{
    mDebugPrintWeight = on;
}

void WeightDisplayItem::Update(bool& redrawRequired)
{
    if (!mRedrawRequired)
    {
        return;
    }

    redrawRequired = true;
    DisplayWeightString(mPrintBuffer);
    mRedrawRequired = false;
}