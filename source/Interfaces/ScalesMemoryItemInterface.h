#pragma once

namespace coffeescales::weight
{

class ScalesMemoryItemInterface
{
public:
    ~ScalesMemoryItemInterface() = default;
    virtual void Init() = 0;
    virtual float GetCalibrationFactor() const = 0;
    virtual void SetCalibrationFactor(float factor) = 0;
};

}