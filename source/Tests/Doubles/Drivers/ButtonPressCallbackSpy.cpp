#include "ButtonPressCallbackSpy.h"

using namespace coffeescales::drivers;

void ButtonPressCallbackSpy::Reset()
{
    OnButtonPressCalled = false;
    Button = buttons::Button::Count;
}

void ButtonPressCallbackSpy::OnButtonPress(buttons::Button button, const uint32_t tick)
{
    OnButtonPressCalled = true;
    Button = button;
    TickMs = tick;
}