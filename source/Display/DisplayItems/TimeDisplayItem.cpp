#include "TimeDisplayItem.h"

#include <cmath>
#include <cstdio>
#include <cstring>

using namespace ::coffeescales::display;

static const char* AutoLabel = "AUTO";

TimeDisplayItem::TimeDisplayItem(DisplayManagerInterface& displayManager, DisplayInterface& display,
    time::BrewTimerInterface& brewTimer, time::TimerAutoStartInterface& timerAutoStart) :
    mDisplayManager(displayManager),
    mDisplay(display),
    mBrewTimer(brewTimer),
    mTimerAutoStart(timerAutoStart)
{
    mDisplayManager.RegisterDisplayItem(this);
}

void TimeDisplayItem::Init()
{
    mBrewTimer.RegisterCallback(this);
    mTimerAutoStart.RegisterCallback(this);
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

void TimeDisplayItem::TimerAutoStartEnabled(bool enabled)
{
    mTimerAutoStartEnabled = enabled;
    mRedrawRequired = true;
}

void TimeDisplayItem::LoadPrintBuffer()
{
    snprintf(mPrintBuffer, PrintBufferSize, "%li:%02li", mDisplayMinutes, mDisplaySeconds);
}

void TimeDisplayItem::DisplayString()
{
    mDisplay.ClearArea(TimerLocationX, TimerLocationY, TimerWidthPx, TimerHeightPx);
    mDisplay.DisplayTextBox(TimerLocationX, TimerLocationY, TimerWidthPx, TimerHeightPx,
        mPrintBuffer, Justify::Center);

    if (mTimerAutoStartEnabled)
    {
        mDisplay.DisplayTextBox(AutoStatusLocationX, AutoStatusLocationY, AutoStatusWidthPx,
            AutoStatusHeightPx, AutoLabel, Justify::Center, FontSize::Small);
    }
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