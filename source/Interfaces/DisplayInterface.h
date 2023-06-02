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
        const char* string, Justify justify, FontSize size = FontSize::Large) = 0;
    virtual void ClearDisplay() const = 0;
    virtual void ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const = 0;
    virtual size_t DisplayHeight() const = 0;
    virtual size_t DisplayWidth() const = 0;
    virtual void Redraw() const = 0;
};

}
