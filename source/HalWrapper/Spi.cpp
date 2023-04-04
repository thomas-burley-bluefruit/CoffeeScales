#include "HalErrorHandler.h"
#include "Spi.h"
#include "stm32l4xx_hal.h"
#include "Utilities.h"

using namespace ::coffeescales::halwrapper;

static constexpr uint32_t SpiCsPin = GPIO_PIN_0;
static GPIO_TypeDef *SpiCsPort = GPIOB;

static GPIO_TypeDef *SpiSckMosiPort = GPIOA;
static constexpr uint32_t SpiSckPin = GPIO_PIN_1;
static constexpr uint32_t SpiMosiPin = GPIO_PIN_7;

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
    sSpi.Init.NSS = SPI_NSS_SOFT;
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

void Spi::SetChipSelect(GpioPinState state)
{
    HAL_GPIO_WritePin(SpiCsPort,
                      SpiCsPin,
                      HalPinState(state));
}

extern "C" void Spi1_MspInit()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = SpiSckPin | SpiMosiPin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(SpiSckMosiPort, &GPIO_InitStruct);

    HAL_GPIO_WritePin(SpiCsPort, SpiCsPin, GPIO_PIN_SET);
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = SpiCsPin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(SpiCsPort, &GPIO_InitStruct);
}

extern "C" void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle)
{

    if (spiHandle->Instance == SPI1)
    {
        __HAL_RCC_SPI1_CLK_DISABLE();

        HAL_GPIO_DeInit(SpiSckMosiPort, SpiSckPin | SpiMosiPin);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
    }
}
