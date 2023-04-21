#pragma once

#include "DisplayItemInterface.h"

namespace coffeescales::display
{

class DisplayItemSpy : public DisplayItemInterface
{
public:
    void DebugPrint(bool on) override;

    bool DebugPrintCalled = false;
    bool DebugPrintValue = false;
};

}

