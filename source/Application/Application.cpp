#include "Application.h"
#include "Instantiation.h"

using namespace ::coffeescales;

static Instantiation mInstantiation;

void Application::Init()
{
    mInstantiation.Init();
}

void Application::Loop()
{
    while (true)
    {
        mInstantiation.Terminal().Task();
        mInstantiation.Scales().Task();
    }
}
