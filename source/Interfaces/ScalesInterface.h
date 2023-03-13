#pragma once

#include "TerminalCallbackInterface.h"

namespace coffeescales::drivers
{

class ScalesInterface
{
public:
    ~ScalesInterface() = default;
    virtual float GetWeightG() const = 0;
};

}