#pragma once

#include <cstddef>

namespace coffeescales::drivers::buttons
{

enum class Button
{
    Tare = 0,
    Timer = 1,
    Count = 2
};

static constexpr size_t MinimumIntervalMs(Button button)
{
    switch (button)
    {
    case Button::Tare:
    case Button::Timer:
    default:
        return 50;
    }
}

}
