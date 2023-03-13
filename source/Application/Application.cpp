#include "Application.h"
#include "Instantiation.h"

static Instantiation mInstantiation;

void Application::Init()
{
    mInstantiation.Init();
}

void Application::Loop()
{
    while (1)
    {
        mInstantiation.Terminal().Task();
    }
}
