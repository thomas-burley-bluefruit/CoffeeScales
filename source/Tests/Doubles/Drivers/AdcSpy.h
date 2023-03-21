#pragma once

#include "AdcDriverInterface.h"

namespace coffeescales::drivers
{

class AdcSpy : public coffeescales::drivers::AdcDriverInterface
{
public:
    bool Read(int32_t &value) const override;
    uint32_t MaxValue() const override;

    const uint32_t MaxAdcValue = 0x7FFFFF;
    mutable size_t ReadCallCount = 0;
    bool ReadSuccess = true;
    int32_t ReadValue = 0;
};

}
