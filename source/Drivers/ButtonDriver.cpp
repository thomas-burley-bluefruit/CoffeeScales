#include "ButtonDriver.h"

#include <cstdio>

using namespace ::coffeescales::drivers;

ButtonDriver::ButtonDriver(buttons::Button button, halwrapper::GpioInterface& buttonGpio,
    halwrapper::ExternalInterruptCallbackRegisterableInterface& interruptTimer,
    halwrapper::TimeInterface& time) :
    mButton(button),
    mButtonGpio(buttonGpio),
    mInterruptTimer(interruptTimer),
    mTime(time),
    MinimumIntervalMs(buttons::MinimumIntervalMs(button))
{
    mLastPressTimeMs = MinimumIntervalMs;
}

void ButtonDriver::Init()
{
    mInterruptTimer.RegisterCallback(this);
}

bool ButtonDriver::Debounce()
{
    const auto timeNowMs = mTime.GetTick();

    if ((timeNowMs - mLastPressTimeMs) < MinimumIntervalMs)
        return false;

    mLastPressTimeMs = timeNowMs;
    return true;
}

void ButtonDriver::RegisterCallback(ButtonPressCallbackInterface* callback)
{
    mCallback = callback;
}

void ButtonDriver::OnExternalInterrupt()
{
    if (mButtonGpio.GetPinState() == halwrapper::GpioPinState::Reset)
    {
        ++mOnTimeMs;
    }
    else
    {
        mOnTimeMs = 0;
        mButtonHeld = false;
    }

    if (mButtonHeld || mOnTimeMs < MinimumOnTimeMs || !Debounce())
    {
        return;
    }

    if (mCallback != nullptr)
        mCallback->OnButtonPress(mButton, mTime.GetTick());

    mButtonHeld = true;
}
