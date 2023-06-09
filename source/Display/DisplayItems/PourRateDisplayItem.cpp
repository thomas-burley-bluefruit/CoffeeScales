#include "PourRateDisplayItem.h"

#include <cstdio>

using namespace ::coffeescales::display;

PourRateDisplayItem::PourRateDisplayItem(DisplayManagerInterface& displayManager,
    DisplayInterface& display, weight::PourRateInterface& pourRate) :
    mDisplay(display)
{
    displayManager.RegisterDisplayItem(this);
    pourRate.RegisterCallback(this);
}

void PourRateDisplayItem::Init()
{
    LoadPrintBuffer();
    mRedrawRequired = true;
}

void PourRateDisplayItem::PourRateUpdate(float pourRateGramsPerSec)
{
    if (mDisplayPourRate == pourRateGramsPerSec
        || (mDisplayPourRate == 0.0f && pourRateGramsPerSec == 0.1f))
    {
        return;
    }

    mDisplayPourRate = pourRateGramsPerSec;
    mRedrawRequired = true;
}

void PourRateDisplayItem::LoadPrintBuffer()
{
    const uint32_t integerGramsPerSec = static_cast<uint32_t>(mDisplayPourRate);
    const uint32_t tenthGramsPerSec = (mDisplayPourRate - integerGramsPerSec) * 10;
    snprintf(mPrintBuffer, PrintBufferSize, "%lu.%lug/s", integerGramsPerSec, tenthGramsPerSec);
}

void PourRateDisplayItem::DisplayString()
{
    mDisplay.ClearArea(LocationX, LocationY, WidthPx, HeightPx);
    mDisplay.DisplayTextBox(LocationX, LocationY, WidthPx, HeightPx, mPrintBuffer, Justify::Right);
}

void PourRateDisplayItem::Update(bool& redrawRequired)
{
    if (!mRedrawRequired)
    {
        return;
    }

    redrawRequired = true;
    LoadPrintBuffer();
    DisplayString();
    mRedrawRequired = false;
}

// TODO: no longer used, maybe remove from interface
void PourRateDisplayItem::DebugPrint(bool on) {}