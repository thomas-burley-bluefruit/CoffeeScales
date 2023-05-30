#pragma once

#include "DisplayItemInterface.h"

namespace coffeescales::display
{

class DisplayItemSpy : public DisplayItemInterface
{
  public:
    void Init() override;
    void Update(bool& redrawRequired) override;
    void DebugPrint(bool on) override;

    bool InitCalled = false;

    bool UpdateCalled = false;
    bool RedrawRequired = false;

    bool DebugPrintCalled = false;
    bool DebugPrintValue = false;
};

}
