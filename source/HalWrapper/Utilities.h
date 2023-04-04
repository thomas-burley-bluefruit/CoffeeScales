#pragma once

#include "stm32l4xx_hal.h"
#include "GpioPinState.h"

namespace coffeescales::halwrapper
{
static constexpr GPIO_PinState HalPinState(const GpioPinState state)
{
    return state == GpioPinState::Set ?
           GPIO_PinState::GPIO_PIN_SET :
           GPIO_PinState::GPIO_PIN_RESET;
}

static constexpr GPIO_PinState HalPinState(const bool state)
{
    return state ?
           GPIO_PinState::GPIO_PIN_SET :
           GPIO_PinState::GPIO_PIN_RESET;
}

static constexpr GpioPinState PinState(const bool state)
{
    return state ?
           GpioPinState::Set :
           GpioPinState::Reset;
}

static constexpr GpioPinState PinState(const GPIO_PinState state)
{
    return state == GPIO_PinState::GPIO_PIN_SET ?
           GpioPinState::Set :
           GpioPinState::Reset;
}
}