#include "HalErrorHandler.h"
#include "stm32l4xx_hal.h"

void ErrorHandler(void)
{
    __disable_irq();
    while (1);
}
