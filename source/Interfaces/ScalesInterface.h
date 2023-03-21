#pragma once

#include "TerminalCallbackInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::weight
{

class ScalesInterface
{
public:
    ~ScalesInterface() = default;
    virtual void TareInit() = 0;
    virtual void CalibrateInit() = 0;
    virtual void CalibrateSet() = 0;
    virtual void AdcDebugPrint(bool on) = 0;
    virtual void WeightDebugPrint(bool on) = 0;
    virtual bool RegisterCallback(WeightReadingCallbackInterface *callback) = 0;
};

}