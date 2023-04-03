#pragma once

#include "stm32l4xx_hal.h"

extern "C"
{

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle);

}