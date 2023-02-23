#include <cstring>
#include "stm32l4xx_hal.h"
#include "Application.h"
#include "Terminal.h"

static terminal::Terminal mTerminal;

extern "C"
{

void Init()
{
    mTerminal.Init();
}

void Application()
{
    while (1)
    {
        const char* message = "Hello world!";
        mTerminal.Transmit(message, strlen(message));
        HAL_Delay(400);
    }
}

}