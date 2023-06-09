#pragma once

#include "DisplayFontSize.h"
#include "DisplayJustify.h"
#include <cstddef>
#include <cstdint>

namespace coffeescales::display
{

class DisplayInterface
{
  public:
    ~DisplayInterface() = default;
    virtual void DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight,
        const char* string, Justify justify, FontSize size = FontSize::Medium) = 0;
    virtual void DrawLine(int16_t startX, int16_t startY, int16_t endX, int16_t endY) = 0;
    virtual void DrawBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight) = 0;
    virtual void ClearDisplay() const = 0;
    virtual void ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const = 0;
    virtual size_t DisplayHeight() const = 0;
    virtual size_t DisplayWidth() const = 0;
    virtual void Redraw() const = 0;
};

}
