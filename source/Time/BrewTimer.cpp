#include "BrewTimer.h"

using namespace coffeescales::time;

BrewTimer::BrewTimer(halwrapper::SystemInterface& system,
    drivers::ButtonDriverInterface& timerButton) :
    mSystem(system),
    mTimerButton(timerButton)
{
    mCallbacks.fill(nullptr);
}

void BrewTimer::Init()
{
    mTimerButton.RegisterCallback(this);
}

void BrewTimer::Task()
{
    if (mStartRequested)
        ActionStart();

    if (mResetRequested)
        ActionReset();

    if (!mRunning)
        return;

    auto ticksSinceStart = mSystem.GetTick() - mStartTick;

    auto minutes = ticksSinceStart / 60000;
    auto seconds = (ticksSinceStart - (minutes * 60000)) / 1000;

    if (seconds == mSeconds && minutes == mMinutes)
        return;

    mMinutes = minutes;
    mSeconds = seconds;
    UpdateSubscribers();
}

void BrewTimer::Start()
{
    mStartRequested = true;
}

void BrewTimer::ActionStart()
{
    mStartRequested = false;
    mRunning = true;
    mStartTick = mSystem.GetTick();
}

void BrewTimer::Reset()
{
    mResetRequested = true;
}

void BrewTimer::ActionReset()
{
    mResetRequested = false;
    mRunning = false;
    mMinutes = 0;
    mSeconds = 0;
    UpdateSubscribers();
}

bool BrewTimer::RegisterCallback(TimerIncrementCallbackInterface* callback)
{
    if (mCallbackCount >= MaxCallbacks)
        return false;

    mCallbacks[mCallbackCount++] = callback;
    return true;
}

void BrewTimer::UpdateSubscribers()
{
    for (size_t i = 0; i < mCallbackCount; ++i)
    {
        if (mCallbacks[i] == nullptr)
            break;
        mCallbacks[i]->TimeUpdate(mMinutes, mSeconds);
    }
}

void BrewTimer::OnButtonPress(const drivers::buttons::Button button, const uint32_t tickMs)
{
    if (mRunning)
    {
        mResetRequested = true;
    }
    else
    {
        mStartRequested = true;
    }
}
