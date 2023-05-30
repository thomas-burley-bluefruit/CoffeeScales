#include "DisplayItemSpy.h"

using namespace coffeescales::display;

void DisplayItemSpy::Init()
{
    InitCalled = true;
}

void DisplayItemSpy::Update(bool& redrawRequired)
{
    UpdateCalled = true;
    if (RedrawRequired)
    {
        redrawRequired = true;
    }
}

void DisplayItemSpy::DebugPrint(bool on)
{
    DebugPrintCalled = true;
    DebugPrintValue = on;
}
