#pragma once

#include "DisplayInterface.h"
#include "ScalesInterface.h"
#include "TerminalInterface.h"
#include "WeightReadingCallbackInterface.h"

#include <cstddef>

namespace coffeescales::display
{

class WeightDisplayItem : public weight::WeightReadingCallbackInterface
{
public:
    WeightDisplayItem(DisplayInterface &display, weight::ScalesInterface &scales,
                      terminal::TerminalInterface &terminal);
    void Init();
    void WeightDebugPrint(bool on);
    void NewWeightReadingMg(int32_t weightMg) override;

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
