#pragma once

#include "DisplayInterface.h"
#include "DisplayItemInterface.h"
#include "ScalesInterface.h"
#include "TerminalInterface.h"
#include "WeightReadingCallbackInterface.h"

#include <cstddef>

namespace coffeescales::display
{

class WeightDisplayItem : public weight::WeightReadingCallbackInterface, public DisplayItemInterface
{
public:
    WeightDisplayItem(DisplayInterface &display, weight::ScalesInterface &scales,
                      terminal::TerminalInterface &terminal);
    void Init();
    void DebugPrint(bool on) override;
    void NewWeightReadingMg(int32_t weightMg) override;

    static constexpr int16_t LocationX = 128;
    static constexpr int16_t LocationY = 0;
    static constexpr int16_t WidthPx = 128;
    static constexpr int16_t HeightPx = 64;

private:
    DisplayInterface &mDisplay;
    weight::ScalesInterface &mScales;
    terminal::TerminalInterface &mTerminal;


    static constexpr size_t PrintBufferSize = 8;
    char mPrintBuffer[PrintBufferSize]{0};

    int32_t mLastGramsDisplayed = 0;
    int32_t mLastDeciGramsDisplayed = 0;

    bool mDebugPrintWeight = false;

    void DisplayWeightString(const char *string);
};

}
