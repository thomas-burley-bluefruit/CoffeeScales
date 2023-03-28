#include "ScalesMemoryItem.h"

using namespace coffeescales::weight;

ScalesMemoryItem::ScalesMemoryItem(const drivers::PersistentMemoryInterface &eeprom) : mEeprom(
        eeprom)
{
}

void ScalesMemoryItem::Init()
{
    Get();
}

float ScalesMemoryItem::GetCalibrationFactor() const
{
    return mCalibrationFactor;
}

void ScalesMemoryItem::SetCalibrationFactor(float factor)
{
    mCalibrationFactor = factor;
    Set();
}

void ScalesMemoryItem::Get()
{
    mEeprom.Read(Address, reinterpret_cast<uint8_t *>(&mCalibrationFactor),
                 sizeof(mCalibrationFactor));
}

void ScalesMemoryItem::Set()
{
    mEeprom.Write(Address, reinterpret_cast<uint8_t *>(&mCalibrationFactor),
                  sizeof(mCalibrationFactor));
}
