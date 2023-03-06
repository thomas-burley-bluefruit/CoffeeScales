#pragma once

#include "GpioInterface.h"
#include "DelayInterface.h"

namespace halwrapper
{

class SystemInterface : public GpioInterface, public DelayInterface
{
public:
    ~SystemInterface() = default;
};

}