#pragma once

#include "DisplayInterface.h"
#include "DisplayItemInterface.h"
#include "DisplayManagerInterface.h"
#include "ScalesInterface.h"
#include "TerminalInterface.h"
#include "WeightReadingCallbackInterface.h"

#include <cstddef>

namespace coffeescales::display
{

class WeightDisplayItem : public weight::WeightReadingCallbackInterface, public DisplayItemInterface
{
  public:
    WeightDisplayItem(DisplayManagerInterface& displayManager, DisplayInterface& display,
        weight::ScalesInterface& scales, terminal::TerminalInterface& terminal);

    // DisplayItemInterface
    void Init() override;
    void Update(bool& redrawRequired) override;
    void DebugPrint(bool on) override;

    // WeightReadingCallbackInterface
    void NewWeightReadingMg(int32_t weightMg) override;

    static constexpr int16_t LocationX = 0;
    static constexpr int16_t LocationY = 0;
    static constexpr int16_t WidthPx = 160;
    static constexpr int16_t HeightPx = 64;

  private:
    DisplayManagerInterface& mDisplayManager;
    DisplayInterface& mDisplay;
    weight::ScalesInterface& mScales;
    terminal::TerminalInterface& mTerminal;

    static constexpr size_t PrintBufferSize = 8;
    char mPrintBuffer[PrintBufferSize] {0};

    bool mRedrawRequired = false;
    int32_t mLastGramsDisplayed = 0;
    int32_t mLastDeciGramsDisplayed = 0;

    bool mDebugPrintWeight = false;

    void LoadPrintBuffer();
    void DisplayWeightString(const char* string);
};

}
