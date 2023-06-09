#pragma once

#include "DisplayInterface.h"
#include "DisplayItemInterface.h"
#include "DisplayManagerInterface.h"
#include "PourRateInterface.h"
#include "PourRateUpdateCallbackInterface.h"

namespace coffeescales::display
{

class PourRateDisplayItem :
    public DisplayItemInterface,
    public weight::PourRateUpdateCallbackInterface
{
  public:
    PourRateDisplayItem(DisplayManagerInterface& displayManager, DisplayInterface& display,
        weight::PourRateInterface& pourRate);

    // DisplayItemInterface
    void Init() override;
    void Update(bool& redrawRequired) override;
    void DebugPrint(bool on) override;

    // PourRateUpdateCallbackInterface
    void PourRateUpdate(float pourRateGramsPerSec) override;

    static constexpr int16_t LocationX = 160;
    static constexpr int16_t LocationY = 32;
    static constexpr int16_t WidthPx = 96;
    static constexpr int16_t HeightPx = 32;

  private:
    DisplayInterface& mDisplay;

    bool mRedrawRequired = false;
    static constexpr size_t PrintBufferSize = 16;
    char mPrintBuffer[PrintBufferSize] {0};

    float mDisplayPourRate = 0.0f;

    void LoadPrintBuffer();
    void DisplayString();
};

}
