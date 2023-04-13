#include "DisplayItemSpy.h"

using namespace coffeescales::display;

void DisplayItemSpy::DebugPrint(bool on)
{
    DebugPrintCalled = true;
    DebugPrintValue = on;
}
