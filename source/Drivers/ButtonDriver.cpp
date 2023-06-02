#include "ButtonDriver.h"

#include <cassert>
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
    assert(mCallbackCount < MaxCallbacks);
    mCallbacks[mCallbackCount++] = callback;
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

    for (uint32_t i = 0; i < mCallbackCount; ++i)
    {
        mCallbacks[i]->OnButtonPress(mButton, mTime.GetTick());
    }

    mButtonHeld = true;
}
