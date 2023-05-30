#include "TimerButtonGpio.h"
#include "stm32l4xx_hal.h"

using namespace ::coffeescales::halwrapper;

static constexpr uint32_t TimerButtonPin = GPIO_PIN_4;
static GPIO_TypeDef* TimerButtonGpioPort = GPIOB;
static constexpr IRQn_Type TimerButtonExtiIrqn = EXTI4_IRQn;

static ExternalInterruptCallbackInterface* mCallback = nullptr;

void TimerButtonGpio::Init()
{
    GPIO_InitTypeDef gpioInit = {0};
    gpioInit.Pin = TimerButtonPin;
    gpioInit.Mode = GPIO_MODE_IT_FALLING;
    gpioInit.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(TimerButtonGpioPort, &gpioInit);

    HAL_NVIC_SetPriority(TimerButtonExtiIrqn, 0, 0);
    HAL_NVIC_EnableIRQ(TimerButtonExtiIrqn);
}

void TimerButtonGpio::RegisterCallback(ExternalInterruptCallbackInterface* callback)
{
    mCallback = callback;
}

extern "C" void EXTI4_IRQHandler(void)
{
    if (__HAL_GPIO_EXTI_GET_IT(TimerButtonPin) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(TimerButtonPin);
        mCallback->OnExternalInterrupt();
    }
}
