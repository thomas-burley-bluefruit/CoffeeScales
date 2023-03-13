#pragma once

#include "GpioInterface.h"
#include "DelayInterface.h"

namespace coffeescales::halwrapper
{

class SystemInterface : public GpioInterface, public DelayInterface
{
public:
    ~SystemInterface() = default;
};

}