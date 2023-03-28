#pragma once

#include "ScalesMemoryItemInterface.h"
#include "PersistentMemoryInterface.h"

namespace coffeescales::weight
{

class ScalesMemoryItem final : public ScalesMemoryItemInterface
{
public:
    explicit ScalesMemoryItem(const drivers::PersistentMemoryInterface &eeprom);
    void Init() override;
    [[nodiscard]] float GetCalibrationFactor() const override;
    void SetCalibrationFactor(float factor) override;

    static constexpr uint16_t Address = 0x0000;
    static constexpr float DefaultCalibrationFactor = 8.0f;

private:
    void Get();
    void Set();

    const drivers::PersistentMemoryInterface &mEeprom;
    float mCalibrationFactor = 0.0f;
};

}
