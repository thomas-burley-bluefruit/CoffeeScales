#pragma once

#include <cstdint>

namespace coffeescales::drivers
{

class HX711DriverInterface
{
public:
    ~HX711DriverInterface() = default;
    virtual bool ReadAdcValue(int32_t& value) const = 0;
};

}
