#include "HalErrorHandler.h"
#include "Uart.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"

using namespace ::coffeescales::halwrapper;

static UART_HandleTypeDef sUart;
static ReceiveInterruptCallbackInterface *sCallback = nullptr;

static constexpr uint32_t UartTxPin = GPIO_PIN_2;
static constexpr uint32_t UartRxPin = GPIO_PIN_15;
static constexpr uint32_t TimeoutMs = 10;


Uart::Uart()
= default;

void Uart::Init()
{
    sUart.Instance = USART2;
    sUart.Init.BaudRate = 115200;
    sUart.Init.WordLength = UART_WORDLENGTH_8B;
    sUart.Init.StopBits = UART_STOPBITS_1;
    sUart.Init.Parity = UART_PARITY_NONE;
    sUart.Init.Mode = UART_MODE_TX_RX;
    sUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    sUart.Init.OverSampling = UART_OVERSAMPLING_16;
    sUart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    sUart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&sUart) != HAL_OK)
        ErrorHandler();
}

void Uart::Transmit(const uint8_t *txData, size_t size) const
{
    HAL_UART_Transmit(&sUart,
                      txData,
                      size,
                      TimeoutMs);
}

void Uart::SetCallback(ReceiveInterruptCallbackInterface *callback) const
{
    sCallback = callback;
}

extern "C" void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    if (huart->Instance == USART2)
    {
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
        PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

        __HAL_RCC_USART2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = UartTxPin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = UartRxPin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF3_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // USART2 interrupt Init
        HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);

        // Receive Data register not empty interrupt
        __HAL_UART_ENABLE_IT(&sUart, UART_IT_RXNE);
        // Error interrupt(Frame error, noise error, overrun error)
        __HAL_UART_ENABLE_IT(&sUart, UART_IT_ERR);
        // Parity Error interrupt
        __HAL_UART_ENABLE_IT(&sUart, UART_IT_PE);
    }
}

extern "C" void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, UartTxPin | UartRxPin);
    }
}

extern "C" void USART2_IRQHandler(void)
{
    // Overrun, Noise, Framing, Parity error occurred
    if (__HAL_UART_GET_FLAG(&sUart, UART_FLAG_ORE) ||
        __HAL_UART_GET_FLAG(&sUart, UART_FLAG_NE) ||
        __HAL_UART_GET_FLAG(&sUart, UART_FLAG_FE) ||
        __HAL_UART_GET_FLAG(&sUart, UART_FLAG_PE))
    {
        // macro will clear any of the above flags
        __HAL_UART_CLEAR_PEFLAG(&sUart);
        if (sCallback != nullptr)
            sCallback->OnReceiveError();
        return;
    }
    uint8_t byte = 0x00;
    HAL_UART_Receive(&sUart, &byte, 1, TimeoutMs);
    if (sCallback != nullptr)
        sCallback->OnReceiveInterrupt(byte);
}
