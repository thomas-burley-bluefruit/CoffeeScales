#pragma once

#include "DisplayItemInterface.h"

namespace coffeescales::display
{

class DisplayManagerInterface
{
  public:
    ~DisplayManagerInterface() = default;
    virtual bool RegisterDisplayItem(DisplayItemInterface* displayItem) = 0;
};

}
