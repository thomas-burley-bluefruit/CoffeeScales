#pragma once

#include <cstddef>

namespace coffeescales::drivers::buttons
{

enum class Button
{
    Tare = 0,
    Count = 1
};

static constexpr size_t MinimumIntervalMs(Button button)
{
    switch (button)
    {
        case Button::Tare:
        default:
            return 100;
    }
}

}