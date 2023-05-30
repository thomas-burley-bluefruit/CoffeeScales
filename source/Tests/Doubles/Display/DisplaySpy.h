#pragma once

#include "DisplayInterface.h"

#include <cstddef>

namespace coffeescales::display
{

class DisplaySpy final : public DisplayInterface
{
  public:
    void Redraw() const override;
    void DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight,
        const char* string, Justify justify) override;
    size_t DisplayHeight() const override;
    size_t DisplayWidth() const override;
    void ClearDisplay() const override;
    void ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const override;

    mutable bool RedrawCalled = false;
    bool DisplayTextBoxCalled = false;
    int16_t DisplayTextBoxX = 0;
    int16_t DisplayTextBoxY = 0;
    int16_t DisplayTextBoxWidth = 0;
    int16_t DisplayTextBoxHeight = 0;
    static constexpr size_t StringBufferSize = 128;
    char StringBuffer[StringBufferSize] {0};
    Justify DisplayTextBoxJustify = Justify::Left;

    size_t DisplayHeightValue = 64;
    size_t DisplayWidthValue = 128;

    mutable bool ClearDisplayCalled = false;

    mutable bool ClearAreaCalled = false;
    mutable int16_t ClearAreaX = 0;
    mutable int16_t ClearAreaY = 0;
    mutable int16_t ClearAreaWidth = 0;
    mutable int16_t ClearAreaHeight = 0;
};

}
