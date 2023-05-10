#include "TareButtonGpio.h"
#include "stm32l4xx_hal.h"

using namespace ::coffeescales::halwrapper;

static constexpr uint32_t TareButtonPin = GPIO_PIN_0;
static GPIO_TypeDef *TareButtonGpioPort = GPIOA;
static constexpr IRQn_Type TareButtonExtiIrqn = EXTI0_IRQn;

GpioInterruptCallbackInterface *mCallback = nullptr;

void TareButtonGpio::Init()
{
    GPIO_InitTypeDef gpioInit = {0};
    gpioInit.Pin = TareButtonPin;
    gpioInit.Mode = GPIO_MODE_IT_FALLING;
    gpioInit.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(TareButtonGpioPort, &gpioInit);

    HAL_NVIC_SetPriority(TareButtonExtiIrqn, 0, 0);
    HAL_NVIC_EnableIRQ(TareButtonExtiIrqn);
}

void TareButtonGpio::SetCallback(GpioInterruptCallbackInterface *callback)
{
    mCallback = callback;
}

extern "C" void EXTI0_IRQHandler(void)
{
    if (__HAL_GPIO_EXTI_GET_IT(TareButtonPin) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(TareButtonPin);
        mCallback->OnReceiveInterrupt();
    }
}
