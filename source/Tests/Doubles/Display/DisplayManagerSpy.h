#pragma once

#include "DisplayManagerInterface.h"

namespace coffeescales::display
{

class DisplayManagerSpy : public DisplayManagerInterface
{
  public:
    bool RegisterDisplayItem(DisplayItemInterface* displayItem) override;

    bool RegisterDisplayItemCalled = true;
    DisplayItemInterface* RegisteredDisplayItem = nullptr;
};

}