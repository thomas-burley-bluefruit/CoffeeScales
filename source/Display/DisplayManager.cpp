#include "DisplayManager.h"

#include <cassert>

using namespace coffeescales::display;

DisplayManager::DisplayManager(DisplayInterface& display) :
    mDisplay(display)
{
}

void DisplayManager::Init()
{
    assert(mDisplayItemCount > 0);

    for (uint32_t i = 0; i < mDisplayItemCount; ++i)
    {
        mDisplayItems[i]->Init();
    }
}

void DisplayManager::Task()
{
    bool redrawRequired = false;

    for (uint32_t i = 0; i < mDisplayItemCount; ++i)
    {
        mDisplayItems[i]->Update(redrawRequired);
    }

    if (redrawRequired)
    {
        mDisplay.Redraw();
    }
}

bool DisplayManager::RegisterDisplayItem(DisplayItemInterface* callback)
{
    if (mDisplayItemCount >= MaxDisplayItems)
        return false;

    mDisplayItems[mDisplayItemCount++] = callback;
    return true;
}
