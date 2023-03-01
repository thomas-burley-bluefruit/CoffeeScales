#include "Application.h"
#include "Instantiation.h"

static Instantiation mInstantiation;

void Application_Init()
{
    mInstantiation.Init();
}

void Application_Loop()
{
    while (1)
    {
        const char* message = "Hello world!\n";
        mInstantiation.Terminal().TextOut(message);
        mInstantiation.Delay().DelayMs(500);
    }
}
