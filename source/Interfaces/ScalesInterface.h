#pragma once

#include "TerminalCallbackInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::weight
{

class ScalesInterface
{
public:
    ~ScalesInterface() = default;
    virtual void StartTare() = 0;
    virtual bool RegisterCallback(WeightReadingCallbackInterface *callback) = 0;
};

}