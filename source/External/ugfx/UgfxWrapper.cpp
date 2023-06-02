#include "UgfxWrapper.h"
#include "gfx.h"
#include "UgfxUtilities.h"

using namespace coffeescales::display;

static const gFont LargeFont = gdispOpenFont("DejaVuSans20");
static const gFont SmallFont = gdispOpenFont("DejaVuSans10");

void UgfxWrapper::Redraw() const
{
    gdispFlush();
}

void UgfxWrapper::DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight,
    const char* string, coffeescales::display::Justify justify, FontSize size)
{
    gFont font;
    switch (size)
    {
    case FontSize::Large:
        font = LargeFont;
        break;
    case FontSize::Small:
        font = SmallFont;
        break;
    default:
        font = LargeFont;
        break;
    }

    gdispDrawStringBox(x, y, boxWidth, boxHeight, string, font, White, UgfxJustify(justify));
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

void UgfxWrapper::ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const
{
    gdispFillArea(x, y, width, height, Black);
}
