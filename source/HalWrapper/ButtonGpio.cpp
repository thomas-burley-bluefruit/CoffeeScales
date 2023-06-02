#include "ButtonGpio.h"
#include "Utilities.h"

using namespace ::coffeescales::halwrapper;

ButtonGpio::ButtonGpio(GPIO_TypeDef* const port, const uint32_t pin) :
    mPort(port),
    mPin(pin)
{
}

void ButtonGpio::Init()
{
    GPIO_InitTypeDef gpioInit = {0};
    gpioInit.Pin = mPin;
    gpioInit.Mode = GPIO_MODE_INPUT;
    gpioInit.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(mPort, &gpioInit);
}

GpioPinState ButtonGpio::GetPinState() const
{
    return PinState(HAL_GPIO_ReadPin(mPort, mPin));
}
