#pragma once

#include "BrewTimerInterface.h"
#include "DisplayInterface.h"
#include "DisplayItemInterface.h"
#include "DisplayManagerInterface.h"
#include "TimerAutoStartCallbackInterface.h"
#include "TimerAutoStartInterface.h"

#include <cstddef>

namespace coffeescales::display
{

class TimeDisplayItem :
    public DisplayItemInterface,
    public time::TimerIncrementCallbackInterface,
    public time::TimerAutoStartCallbackInterface
{
  public:
    TimeDisplayItem(DisplayManagerInterface& displayManager, DisplayInterface& display,
        time::BrewTimerInterface& brewTimer, time::TimerAutoStartInterface& timerAutoStart);

    // DisplayItemInterface
    void Init() override;
    void Update(bool& redrawRequired) override;
    void DebugPrint(bool on) override;

    // TimerIncrementCallbackInterface
    void TimeUpdate(uint32_t minutes, uint32_t seconds) override;

    // TimerAutoStartCallbackInterface
    void TimerAutoStartEnabled(bool enabled) override;

    static constexpr int16_t TimerLocationX = 160;
    static constexpr int16_t TimerLocationY = 0;
    static constexpr int16_t TimerWidthPx = 96;
    static constexpr int16_t TimerHeightPx = 32;

    static constexpr int16_t AutoStatusLocationX = 165;
    static constexpr int16_t AutoStatusLocationY = 0;
    static constexpr int16_t AutoStatusWidthPx = 32;
    static constexpr int16_t AutoStatusHeightPx = 32;

  private:
    DisplayManagerInterface& mDisplayManager;
    DisplayInterface& mDisplay;
    time::BrewTimerInterface& mBrewTimer;
    time::TimerAutoStartInterface& mTimerAutoStart;

    bool mRedrawRequired = false;
    static constexpr size_t PrintBufferSize = 8;
    char mPrintBuffer[PrintBufferSize] {0};

    uint32_t mDisplayMinutes = 0;
    int32_t mDisplaySeconds = 0;

    bool mTimerAutoStartEnabled = false;

    void LoadPrintBuffer();
    void DisplayString();
};

}
