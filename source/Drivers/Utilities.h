#pragma once

#include <bitset>
#include <cstdint>
#include <cmath>

namespace coffeescales::drivers
{

class Utilities
{
public:
    template<size_t bits>
    static constexpr int32_t TwosComplementToInt(std::bitset<bits> &data)
    {
        bool negativeValue = data[bits - 1];
        if (negativeValue)
        {
            data.flip();
            return -static_cast<int32_t>(data.to_ulong()) - 1;
        }

        return data.to_ulong();
    }

    template<size_t bits>
    static constexpr std::bitset<bits> IntToTwosComplement(int32_t value)
    {
        if (value >= 0)
            return std::bitset<bits>(value);

        std::bitset<bits> data(std::abs(value));
        data.flip();
        data = std::bitset<bits>(data.to_ulong() + 1);
        return data;
    }
};

}