#include "DisplayManagerSpy.h"

using namespace coffeescales::display;

bool DisplayManagerSpy::RegisterDisplayItem(DisplayItemInterface* displayItem)
{
    RegisterDisplayItemCalled = true;
    RegisteredDisplayItem = displayItem;
    return true;
}
