#include "ButtonPressCallbackSpy.h"

using namespace coffeescales::drivers;

void ButtonPressCallbackSpy::Reset()
{
    OnButtonPressCalled = false;
    Button = buttons::Button::Count;
}

void ButtonPressCallbackSpy::OnButtonPress(buttons::Button button)
{
    OnButtonPressCalled = true;
    Button = button;
}