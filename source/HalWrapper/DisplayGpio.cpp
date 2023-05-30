#include "DisplayGpio.h"
#include "HalErrorHandler.h"
#include "stm32l4xx_hal.h"
#include "Utilities.h"

using namespace ::coffeescales::halwrapper;

static GPIO_TypeDef* DisplayPort = GPIOB;
static constexpr uint32_t SpiSckPin = GPIO_PIN_3;
static constexpr uint32_t SpiMosiPin = GPIO_PIN_5;
static constexpr uint32_t DisplayResetPin = GPIO_PIN_6;
static constexpr uint32_t DisplayDcPin = GPIO_PIN_7;

static SPI_HandleTypeDef sSpi;
static constexpr uint32_t TimeoutMs = 10;

extern "C"
{

    void DisplayGpio_Init()
    {
        sSpi.Instance = SPI3;
        sSpi.Init.Mode = SPI_MODE_MASTER;
        sSpi.Init.Direction = SPI_DIRECTION_1LINE;
        sSpi.Init.DataSize = SPI_DATASIZE_8BIT;
        sSpi.Init.CLKPolarity = SPI_POLARITY_LOW;
        sSpi.Init.CLKPhase = SPI_PHASE_1EDGE;
        sSpi.Init.NSS = SPI_NSS_SOFT;
        sSpi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
        sSpi.Init.FirstBit = SPI_FIRSTBIT_MSB;
        sSpi.Init.TIMode = SPI_TIMODE_DISABLE;
        sSpi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
        sSpi.Init.CRCPolynomial = 7;
        sSpi.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
        sSpi.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
        if (HAL_SPI_Init(&sSpi) != HAL_OK)
            ErrorHandler();
    }

    void DisplayGpio_SetResetPin(bool state)
    {
        HAL_GPIO_WritePin(DisplayPort, DisplayResetPin, HalPinState(state));
    }

    bool DisplayGpio_Transmit(const uint8_t* data, uint16_t size)
    {
        auto result = HAL_SPI_Transmit(&sSpi, (uint8_t*)data, size, TimeoutMs);
        return result == HAL_OK;
    }

    void DisplayGpio_SetDcPin(bool state)
    {
        HAL_GPIO_WritePin(DisplayPort, DisplayDcPin, HalPinState(state));
    }

    void Spi3_MspInit()
    {
        __HAL_RCC_SPI3_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = SpiSckPin | SpiMosiPin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
        HAL_GPIO_Init(DisplayPort, &GPIO_InitStruct);

        GPIO_InitStruct = {0};
        HAL_GPIO_WritePin(DisplayPort, DisplayResetPin | DisplayDcPin, GPIO_PIN_SET);
        __HAL_RCC_GPIOB_CLK_ENABLE();
        GPIO_InitStruct.Pin = DisplayResetPin | DisplayDcPin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(DisplayPort, &GPIO_InitStruct);
    }
}
