#pragma once

namespace coffeescales::display
{

class DisplayItemInterface
{
  public:
    ~DisplayItemInterface() = default;
    virtual void Init() = 0;
    virtual void Update(bool& redrawRequired) = 0;
    virtual void DebugPrint(bool on) = 0;
};

}
