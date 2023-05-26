#include "TimeDisplayItem.h"

#include <cmath>
#include <cstdio>
#include <cstring>

using namespace ::coffeescales::display;

TimeDisplayItem::TimeDisplayItem(DisplayManagerInterface& displayManager, DisplayInterface& display,
    time::BrewTimerInterface& brewTimer) :
    mDisplayManager(displayManager),
    mDisplay(display),
    mBrewTimer(brewTimer)
{
    mDisplayManager.RegisterDisplayItem(this);
}

void TimeDisplayItem::Init()
{
    mBrewTimer.RegisterCallback(this);
    LoadPrintBuffer();
    mRedrawRequired = true;
}

void TimeDisplayItem::TimeUpdate(uint32_t minutes, uint32_t seconds)
{
    mDisplayMinutes = minutes;
    mDisplaySeconds = seconds;
    LoadPrintBuffer();
    mRedrawRequired = true;
}

void TimeDisplayItem::LoadPrintBuffer()
{
    snprintf(mPrintBuffer, PrintBufferSize, "%li:%02li", mDisplayMinutes, mDisplaySeconds);
}

void TimeDisplayItem::DisplayString()
{
    mDisplay.ClearArea(LocationX, LocationY, WidthPx, HeightPx);
    mDisplay.DisplayTextBox(LocationX, LocationY, WidthPx, HeightPx, mPrintBuffer, Justify::Center);
}

void TimeDisplayItem::Update(bool& redrawRequired)
{
    if (!mRedrawRequired)
    {
        return;
    }

    redrawRequired = true;
    DisplayString();
    mRedrawRequired = false;
}

// TODO: no longer used, maybe remove from interface
void TimeDisplayItem::DebugPrint(bool on) {}