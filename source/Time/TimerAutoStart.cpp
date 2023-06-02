#include "TimerAutoStart.h"

using namespace coffeescales::time;

TimerAutoStart::TimerAutoStart(BrewTimerInterface& brewTimer, weight::ScalesInterface& scales,
    drivers::ButtonDriverInterface& timerButton) :
    mBrewTimer(brewTimer)
{
    scales.RegisterCallback(this);
    timerButton.RegisterCallback(this);
}

void TimerAutoStart::Enable()
{
    mEnabled = true;
    mReferenceWeightMg = mLastWeightReadingMg;

    if (mCallback != nullptr)
    {
        mCallback->TimerAutoStartEnabled(mEnabled);
    }
}

void TimerAutoStart::RegisterCallback(TimerAutoStartCallbackInterface* callback)
{
    mCallback = callback;
}

void TimerAutoStart::NewWeightReadingMg(int32_t weightMg)
{
    mLastWeightReadingMg = weightMg;

    if (!mEnabled)
    {
        return;
    }

    const int32_t thresholdWeightMg = mLastWeightReadingMg - mReferenceWeightMg;
    if (thresholdWeightMg <= ThresholdMg)
    {
        return;
    }

    mBrewTimer.Start();
    mEnabled = false;

    if (mCallback != nullptr)
    {
        mCallback->TimerAutoStartEnabled(mEnabled);
    }
}

void TimerAutoStart::OnButtonPress(const drivers::buttons::Button button, const uint32_t tickMs)
{
    if (button != drivers::buttons::Button::Timer)
    {
        return;
    }

    if ((tickMs - mLastButtonPressTickMs) < DoubleClickWindowMs)
    {
        Enable();
    }

    mLastButtonPressTickMs = tickMs;
}