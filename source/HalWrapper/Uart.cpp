#include "Uart.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"

static UART_HandleTypeDef mUart;
static constexpr uint32_t TimeoutMs = 10;

using namespace ::halwrapper;

Uart::Uart()
{
}

void Uart::Init()
{
    mUart.Instance = USART2;
    mUart.Init.BaudRate = 115200;
    mUart.Init.WordLength = UART_WORDLENGTH_8B;
    mUart.Init.StopBits = UART_STOPBITS_1;
    mUart.Init.Parity = UART_PARITY_NONE;
    mUart.Init.Mode = UART_MODE_TX_RX;
    mUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    mUart.Init.OverSampling = UART_OVERSAMPLING_16;
    mUart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    mUart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
}

void Uart::Transmit(const uint8_t* txData, size_t size) const
{
    HAL_UART_Transmit(&mUart,
                      txData,
                      size,
                      TimeoutMs);
}