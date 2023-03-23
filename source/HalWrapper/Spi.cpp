#include "HalErrorHandler.h"
#include "Spi.h"
#include "stm32l4xx_hal.h"

using namespace ::coffeescales::halwrapper;

static SPI_HandleTypeDef sSpi;
static constexpr uint32_t TimeoutMs = 10;

void Spi::Init()
{
    sSpi.Instance = SPI1;
    sSpi.Init.Mode = SPI_MODE_MASTER;
    sSpi.Init.Direction = SPI_DIRECTION_1LINE;
    sSpi.Init.DataSize = SPI_DATASIZE_8BIT;
    sSpi.Init.CLKPolarity = SPI_POLARITY_LOW;
    sSpi.Init.CLKPhase = SPI_PHASE_1EDGE;
    sSpi.Init.NSS = SPI_NSS_HARD_OUTPUT;
    sSpi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    sSpi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    sSpi.Init.TIMode = SPI_TIMODE_DISABLE;
    sSpi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    sSpi.Init.CRCPolynomial = 7;
    sSpi.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    sSpi.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    if (HAL_SPI_Init(&sSpi) != HAL_OK)
        ErrorHandler();
}

bool Spi::Transmit(const uint8_t *data, uint16_t size)
{
    auto result = HAL_SPI_Transmit(&sSpi, (uint8_t *) data, size, TimeoutMs);
    return result == HAL_OK;
}

bool Spi::Receive(uint8_t *data, uint16_t size)
{
    auto result = HAL_SPI_Receive(&sSpi, data, size, TimeoutMs);
    return result == HAL_OK;
}

extern "C" void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (spiHandle->Instance == SPI1)
    {
        __HAL_RCC_SPI1_CLK_ENABLE();

        /**SPI1 GPIO Configuration
        PA1     ------> SPI1_SCK
        PA7     ------> SPI1_MOSI
        PB0     ------> SPI1_NSS
        */
        GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}

extern "C" void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle)
{

    if (spiHandle->Instance == SPI1)
    {
        __HAL_RCC_SPI1_CLK_DISABLE();

        /**SPI1 GPIO Configuration
        PA1     ------> SPI1_SCK
        PA7     ------> SPI1_MOSI
        PB0     ------> SPI1_NSS
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1 | GPIO_PIN_7);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
    }
}
