#include "ScalesSpy.h"

using namespace ::coffeescales::weight;

void ScalesSpy::TareInit()
{
    TareInitCalled = true;
}

void ScalesSpy::CalibrateInit()
{
    CalibrateInitCalled = true;
}

void ScalesSpy::CalibrateSet()
{
    CalibrateSetCalled = true;
}

void ScalesSpy::AdcDebugPrint(bool on)
{
    AdcDebugPrintCalled = true;
    AdcDebugPrintValue = on;
}

void ScalesSpy::WeightDebugPrint(bool on)
{
    WeightDebugPrintCalled = true;
    WeightDebugPrintValue = on;
}

bool ScalesSpy::RegisterCallback(
        WeightReadingCallbackInterface *callback)
{
    RegisterCallbackCalled = true;
    RegisteredCallback = callback;
    return false;
}
