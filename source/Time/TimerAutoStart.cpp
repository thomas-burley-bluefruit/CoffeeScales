#include "TimerAutoStart.h"

using namespace coffeescales::time;

TimerAutoStart::TimerAutoStart(BrewTimerInterface& brewTimer, weight::ScalesInterface& scales) :
    mBrewTimer(brewTimer),
    mScales(scales)
{
    mScales.RegisterCallback(this);
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
    const int32_t thresholdWeightMg = mLastWeightReadingMg - mReferenceWeightMg;

    if (mEnabled && thresholdWeightMg > ThresholdMg)
    {
        mBrewTimer.Start();
        mEnabled = false;
    }

    if (mCallback != nullptr)
    {
        mCallback->TimerAutoStartEnabled(mEnabled);
    }
}
