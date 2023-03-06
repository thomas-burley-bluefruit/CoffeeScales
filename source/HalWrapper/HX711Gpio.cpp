#include "HX711Gpio.h"
#include "stm32l4xx_hal.h"
#include "Utilities.h"

using namespace ::halwrapper;

static constexpr uint32_t HX711DoutPin = GPIO_PIN_3;
static GPIO_TypeDef* HX711DoutGpioPort = GPIOA;
static constexpr uint32_t HX711PdSckPin = GPIO_PIN_4;
static GPIO_TypeDef* HX711PdSckGpioPort = GPIOA;

void HX711Gpio::Init()
{
    // HX711 data out
    GPIO_InitTypeDef GpioInitDout{0};

    GpioInitDout.Pin = HX711DoutPin;
    GpioInitDout.Mode = GPIO_MODE_INPUT;
    GpioInitDout.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(HX711DoutGpioPort, &GpioInitDout);

    HAL_GPIO_WritePin(HX711PdSckGpioPort, HX711PdSckPin, GPIO_PIN_RESET);

    // HX711 clock in
    GPIO_InitTypeDef GpioPdSck{0};
    GpioPdSck.Pin = HX711PdSckPin;
    GpioPdSck.Mode = GPIO_MODE_OUTPUT_PP;
    GpioPdSck.Pull = GPIO_NOPULL;
    GpioPdSck.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(HX711PdSckGpioPort, &GpioPdSck);
}

GpioPinState HX711Gpio::GetPinState() const {
    return PinState(HAL_GPIO_ReadPin(HX711DoutGpioPort, HX711DoutPin));
}

void HX711Gpio::SetPinState(const halwrapper::GpioPinState state) {
    HAL_GPIO_WritePin(HX711PdSckGpioPort,
                      HX711PdSckPin,
                      HalPinState(state));
}