#pragma once

#include "DisplayInterface.h"

namespace coffeescales::display
{

class UgfxWrapper final : public DisplayInterface
{
  public:
    void Redraw() const override;
    void DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight,
        const char* string, Justify justify, FontSize size = FontSize::Medium) override;
    void DrawLine(int16_t startX, int16_t startY, int16_t endX, int16_t endY) override;
    void DrawBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight);
    void ClearDisplay() const override;
    void ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const override;
    size_t DisplayHeight() const override;
    size_t DisplayWidth() const override;
};

}
