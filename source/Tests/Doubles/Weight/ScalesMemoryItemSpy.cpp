#include "ScalesMemoryItemSpy.h"

using namespace coffeescales::weight;

void ScalesMemoryItemSpy::Init()
{
}

float ScalesMemoryItemSpy::GetCalibrationFactor() const
{
    GetCalibrationFactorCalled = true;
    return GetCalibrationFactorValue;
}

void ScalesMemoryItemSpy::SetCalibrationFactor(float factor)
{
    SetCalibrationFactorValue = factor;
    SetCalibrationFactorCalled = true;
}
