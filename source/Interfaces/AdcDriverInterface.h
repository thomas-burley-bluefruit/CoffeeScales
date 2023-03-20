#pragma once

#include <cstdint>

namespace coffeescales::drivers
{

class AdcDriverInterface
{
public:
    ~AdcDriverInterface() = default;
    virtual bool Read(int32_t &value) const = 0;
    [[nodiscard]] virtual uint32_t MaxValue() const = 0;
};

}
