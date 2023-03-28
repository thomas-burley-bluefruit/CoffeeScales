#pragma once

#include "ScalesMemoryItemInterface.h"
#include "EepromInterface.h"

namespace coffeescales::weight
{

class ScalesMemoryItem final : public ScalesMemoryItemInterface
{
public:
    explicit ScalesMemoryItem(const drivers::EepromInterface &eeprom);
    void Init() override;
    [[nodiscard]] float GetCalibrationFactor() const override;
    void SetCalibrationFactor(float factor) override;

    static constexpr uint16_t Address = 0x0000;

private:
    void Get();
    void Set();

    const drivers::EepromInterface &mEeprom;
    float mCalibrationFactor = 0.0f;
};

}
