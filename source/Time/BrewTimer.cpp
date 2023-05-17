#include "BrewTimer.h"

using namespace coffeescales::time;

BrewTimer::BrewTimer(halwrapper::SystemInterface &system) : mSystem(system)
{
  mCallbacks.fill(nullptr);
}

void BrewTimer::Task()
{
}

void BrewTimer::StartTimer()
{
}

void BrewTimer::ResetTimer()
{
}

bool BrewTimer::RegisterCallback(TimerIncrementCallbackInterface *callback)
{
  return false;
}
