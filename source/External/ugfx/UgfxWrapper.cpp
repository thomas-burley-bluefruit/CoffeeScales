#include "UgfxWrapper.h"
#include "UgfxUtilities.h"
#include "gfx.h"

using namespace coffeescales::display;

static const gFont Font = gdispOpenFont("UI2");

void UgfxWrapper::DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight,
                                 const char *string, coffeescales::display::Justify justify)
{
//    auto font = gdispScaleFont(Font, 2, 2);
    gdispDrawStringBox(x, y, boxWidth, boxHeight, string, Font, White, UgfxJustify(justify));
}

size_t UgfxWrapper::DisplayHeight() const
{
    return gdispGetHeight();
}

size_t UgfxWrapper::DisplayWidth() const
{
    return gdispGetWidth();
}

void UgfxWrapper::ClearDisplay() const
{
    gdispClear(Black);
}
