#pragma once

#include <cstdint>
#include <cstddef>
#include "DisplayJustify.h"

namespace coffeescales::display
{

class DisplayInterface
{
public:
    ~DisplayInterface() = default;
    virtual void
    DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight, const char *string,
                   Justify justify) = 0;
    virtual void ClearDisplay() const = 0;
    virtual void ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const = 0;
    virtual size_t DisplayHeight() const = 0;
    virtual size_t DisplayWidth() const = 0;
};

}
