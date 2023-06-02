#pragma once

#include "stm32l4xx_hal.h"

#include <cstdint>

namespace coffeescales::halwrapper
{

static constexpr uint32_t TareButtonPin = GPIO_PIN_0;
static GPIO_TypeDef* TareButtonGpioPort = GPIOA;

static constexpr uint32_t TimerButtonPin = GPIO_PIN_4;
static GPIO_TypeDef* TimerButtonGpioPort = GPIOB;

}