#pragma once

namespace coffeescales::display
{

class DisplayItemInterface
{
public:
    ~DisplayItemInterface() = default;
    virtual void DebugPrint(bool on) = 0;
};

}
