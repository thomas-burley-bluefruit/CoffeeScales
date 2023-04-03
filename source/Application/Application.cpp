#include "Application.h"
#include "Instantiation.h"
#include "gfx.h"
#include "DisplayGpio.h"
#include "HalMsp.h"

using namespace ::coffeescales;

static Instantiation mInstantiation;

void Application::Init()
{
    mInstantiation.Init();
    DisplayGpio_Init();
    gfxInit();
    gdispFillArea(0, 0, gdispGetWidth(), gdispGetHeight(), White);
//    auto font = gdispOpenFont("UI2");
//    gdispDrawStringBox(0, 0, gdispGetWidth(), gdispGetHeight(), "Woot!!!", font, White,
//                       justifyCenter);
}

[[noreturn]] void Application::Loop()
{
    while (true)
    {
        mInstantiation.Terminal().Task();
        mInstantiation.Scales().Task();
    }
}
