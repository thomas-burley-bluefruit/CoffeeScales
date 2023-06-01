#include "DisplaySpy.h"

#include <string>

using namespace coffeescales::display;

void DisplaySpy::Redraw() const
{
    RedrawCalled = true;
}

void DisplaySpy::DisplayTextBox(int16_t x, int16_t y, int16_t boxWidth, int16_t boxHeight,
    const char* string, Justify justify, FontSize fontSize)
{
    DisplayTextBoxCalled = true;
    DisplayTextBoxX = x;
    DisplayTextBoxY = y;
    DisplayTextBoxWidth = boxWidth;
    DisplayTextBoxHeight = boxHeight;
    DisplayTextBoxJustify = justify;

    TextsDisplayed.push_back(string);
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

void DisplaySpy::ClearArea(int16_t x, int16_t y, int16_t width, int16_t height) const
{
    ClearAreaCalled = true;
    ClearAreaX = x;
    ClearAreaY = y;
    ClearAreaWidth = width;
    ClearAreaHeight = height;
}
