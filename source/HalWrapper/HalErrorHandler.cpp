#include "HalErrorHandler.h"
#include "stm32l4xx_hal.h"

[[noreturn]] void ErrorHandler()
{
    __disable_irq();
    while (true);
}
