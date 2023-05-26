#pragma once

#include "BrewTimerInterface.h"
#include "DisplayInterface.h"
#include "DisplayItemInterface.h"
#include "DisplayManagerInterface.h"

#include <cstddef>

namespace coffeescales::display
{

class TimeDisplayItem : public time::TimerIncrementCallbackInterface, public DisplayItemInterface
{
  public:
    TimeDisplayItem(DisplayManagerInterface& displayManager, DisplayInterface& display,
        time::BrewTimerInterface& brewTimer);
    void TimeUpdate(uint32_t minutes, uint32_t seconds) override;

    // DisplayItemInterface
    void Init() override;
    void Update(bool& redrawRequired) override;
    void DebugPrint(bool on) override;

    static constexpr int16_t LocationX = 0;
    static constexpr int16_t LocationY = 0;
    static constexpr int16_t WidthPx = 128;
    static constexpr int16_t HeightPx = 64;

  private:
    DisplayManagerInterface& mDisplayManager;
    DisplayInterface& mDisplay;
    time::BrewTimerInterface& mBrewTimer;

    bool mRedrawRequired = false;
    static constexpr size_t PrintBufferSize = 8;
    char mPrintBuffer[PrintBufferSize] {0};

    uint32_t mDisplayMinutes = 0;
    int32_t mDisplaySeconds = 0;

    void LoadPrintBuffer();
    void DisplayString();
};

}
