#pragma once

#include "DisplayInterface.h"

namespace coffeescales::display
{

class UgfxWrapper final : public DisplayInterface
{
public:
    void
    DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight, const char *string,
                   Justify justify) override;
    void ClearDisplay() const override;
    void ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const override;
    size_t DisplayHeight() const override;
    size_t DisplayWidth() const override;
};

}
