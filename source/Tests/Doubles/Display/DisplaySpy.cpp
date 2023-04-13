#include "DisplaySpy.h"

#include <string>

using namespace coffeescales::display;

void DisplaySpy::DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight,
                                const char *string, Justify justify)
{
    DisplayTextBoxCalled = true;
    DisplayTextBoxX = x;
    DisplayTextBoxY = y;
    DisplayTextBoxWidth = boxWidth;
    DisplayTextBoxHeight = boxHeight;
    DisplayTextBoxJustify = justify;

    strncpy_s(StringBuffer, StringBufferSize, string, StringBufferSize);
}

size_t DisplaySpy::DisplayHeight() const
{
    return DisplayHeightValue;
}

size_t DisplaySpy::DisplayWidth() const
{
    return DisplayWidthValue;
}

void DisplaySpy::ClearDisplay() const
{
    ClearDisplayCalled = true;
}
