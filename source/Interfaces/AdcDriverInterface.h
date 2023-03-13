#pragma once

#include <cstdint>

namespace coffeescales::drivers
{

class AdcDriverInterface
{
public:
    ~AdcDriverInterface() = default;
    virtual bool Read(int32_t& value) const = 0;
};

}
