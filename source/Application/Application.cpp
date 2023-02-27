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
        const char* message = "Hello world!\n";
        mInstantiation.Terminal().TextOut(message);
    }
}

}