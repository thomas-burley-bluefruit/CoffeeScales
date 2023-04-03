#include "DisplayGpio.h"
#include "HalMsp.h"
#include "Spi.h"

extern "C"
{

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI1)
        Spi1_MspInit();
    if (hspi->Instance == SPI3)
        Spi3_MspInit();
}

}