#include "ButtonDriver.h"

using namespace ::coffeescales::drivers;

ButtonDriver::ButtonDriver(buttons::Button button, halwrapper::ButtonGpioInterface &buttonGpio,
                           halwrapper::SystemInterface &system)
        : mButton(button), mButtonGpio(buttonGpio), mSystem(system),
          MinimumIntervalMs(buttons::MinimumIntervalMs(button))
{
}

void ButtonDriver::Init()
{
    mButtonGpio.RegisterCallback(this);
}

bool ButtonDriver::Debounce()
{
    auto timeNowMs = mSystem.GetTick();
    if (timeNowMs - mLastPressTimeMs < MinimumIntervalMs)
        return false;

    mLastPressTimeMs = timeNowMs;
    return true;
}

void ButtonDriver::RegisterCallback(ButtonPressCallbackInterface *callback)
{
    mCallback = callback;
}

void ButtonDriver::OnExternalInterrupt()
{
    if (!Debounce())
        return;

    if (mCallback != nullptr)
        mCallback->OnButtonPress(mButton);
}
