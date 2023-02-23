#include <cstring>
#include "stm32l4xx_hal.h"
#include "Application.h"
#include "Instantiation.h"

static Instantiation mInstantiation;

extern "C"
{

void Init()
{
    mInstantiation.Init();
}

void Application()
{
    while (1)
    {
        const char* message = "Hello world!";
        mInstantiation.Terminal().Transmit(message, strlen(message));
        HAL_Delay(400);
    }
}

}