#include "InterruptTimerGpio.h"
#include "HalErrorHandler.h"
#include "stm32l4xx_hal.h"

#include <cassert>
#include <cstddef>

using namespace ::coffeescales::halwrapper;

static TIM_HandleTypeDef sTimer;
static constexpr size_t MaxCallbacks = 8;
static size_t sCallbackCount = 0;
static ExternalInterruptCallbackInterface* sCallbacks[MaxCallbacks] {nullptr};

void InterruptTimerGpio::Init()
{
    // 32MHz / prescaler 1 = 16MHz
    // period of 15999 at 16MHz = reset every 1ms
    sTimer.Instance = TIM7;
    sTimer.Init.Prescaler = 1;
    sTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    sTimer.Init.Period = 15999;
    sTimer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&sTimer) != HAL_OK)
    {
        ErrorHandler();
    }

    TIM_MasterConfigTypeDef sMasterConfig = {0};
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&sTimer, &sMasterConfig) != HAL_OK)
    {
        ErrorHandler();
    }

    auto result = HAL_TIM_Base_Start_IT(&sTimer);
    if (result != HAL_OK)
        ErrorHandler();
}

void InterruptTimerGpio::RegisterCallback(ExternalInterruptCallbackInterface* callback)
{
    assert(sCallbackCount < MaxCallbacks);
    sCallbacks[sCallbackCount++] = callback;
}

extern "C"
{

    void TIM7_IRQHandler(void)
    {
        HAL_TIM_IRQHandler(&sTimer);
    }

    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
    {
        if (htim->Instance != TIM7)
        {
            return;
        }

        for (size_t i = 0; i < sCallbackCount; ++i)
        {
            sCallbacks[i]->OnExternalInterrupt();
        }
    }
}
