#pragma once

#include "ScalesInterface.h"

namespace coffeescales::weight
{

class ScalesSpy final : public ScalesInterface
{
public:
    void TareInit() override;
    void CalibrateInit() override;
    void CalibrateSet() override;
    void AdcDebugPrint(bool on) override;
    void WeightDebugPrint(bool on) override;
    bool RegisterCallback(WeightReadingCallbackInterface *callback) override;

    bool TareInitCalled = false;
    bool CalibrateInitCalled = false;
    bool CalibrateSetCalled = false;
    bool AdcDebugPrintCalled = false;
    bool WeightDebugPrintCalled = false;
    bool RegisterCallbackCalled = false;
    bool AdcDebugPrintValue = false;
    bool WeightDebugPrintValue = false;
};

}
