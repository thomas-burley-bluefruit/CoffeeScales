#include "DelayTimer.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"

static TIM_HandleTypeDef sTimer;
static constexpr uint16_t TimerPrescaler = 31; // period is in units of 1us

using namespace ::coffeescales::halwrapper;

void DelayTimer::Init()
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    sTimer.Instance = TIM6;
    sTimer.Init.Prescaler = TimerPrescaler;
    sTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    sTimer.Init.Period = 65535;
    sTimer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&sTimer) != HAL_OK)
        ErrorHandler();

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&sTimer, &sMasterConfig) != HAL_OK)
        ErrorHandler();

    auto result = HAL_TIM_Base_Start(&sTimer);
    if (result != HAL_OK)
        ErrorHandler();
}

void DelayTimer::ResetCounter()
{
    // TODO: Do we need to clear the event? (NVIC)
    sTimer.Instance->EGR |= TIM_EGR_UG;
}

uint16_t DelayTimer::GetCounter()
{
    return __HAL_TIM_GET_COUNTER(&sTimer);
}

void DelayTimer::ErrorHandler()
{
    while (true) {}
}

extern "C" void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
    if(htim_base->Instance==TIM6)
        __HAL_RCC_TIM6_CLK_ENABLE();
}

extern "C" void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
    if(htim_base->Instance==TIM6)
        __HAL_RCC_TIM6_CLK_DISABLE();
}
