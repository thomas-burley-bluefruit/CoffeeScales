#pragma once

#include "ScalesMemoryItemInterface.h"

namespace coffeescales::weight
{

class ScalesMemoryItemSpy final : public ScalesMemoryItemInterface
{
public:
    void Init() override;
    [[nodiscard]] float GetCalibrationFactor() const override;
    void SetCalibrationFactor(float factor) override;

    mutable bool GetCalibrationFactorCalled = false;
    float GetCalibrationFactorValue = 1.0f;

    mutable bool SetCalibrationFactorCalled = false;
    float SetCalibrationFactorValue = 0.0f;
};

}
