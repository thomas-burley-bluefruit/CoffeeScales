#pragma once

#include <array>

#include "DisplayInterface.h"
#include "DisplayManagerInterface.h"

namespace coffeescales::display
{

class DisplayManager : public DisplayManagerInterface
{
  public:
    DisplayManager(DisplayInterface& display);
    void Init();
    void Task();
    bool RegisterDisplayItem(DisplayItemInterface* displayItem) override;

  private:
    DisplayInterface& mDisplay;

  protected:
    static constexpr size_t MaxDisplayItems = 8;
    uint32_t mDisplayItemCount = 0;
    std::array<DisplayItemInterface*, MaxDisplayItems> mDisplayItems;
};

}
