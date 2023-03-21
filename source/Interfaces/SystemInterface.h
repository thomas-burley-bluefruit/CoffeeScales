#pragma once

#include "GpioInterface.h"
#include "TimeInterface.h"

namespace coffeescales::halwrapper
{

class SystemInterface : public GpioInterface, public TimeInterface
{
public:
    ~SystemInterface() = default;
};

}