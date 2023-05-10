#include "TareButtonDriver.h"

using namespace ::coffeescales::drivers;

TareButtonDriver::TareButtonDriver(halwrapper::ButtonGpioInterface &tareButton,
                                   halwrapper::SystemInterface &system,
                                   terminal::TerminalInterface &terminal) : mTerminal(terminal),
                                                                            mSystem(system)
{
    tareButton.SetCallback(this);
}

void TareButtonDriver::OnReceiveInterrupt()
{
    if (!Debounce())
        return;
    mTerminal.TextOut("Tare!\n");
}

bool TareButtonDriver::Debounce()
{
    auto timeNowMs = mSystem.GetTick();
    if (timeNowMs - mLastPressTimeMs < MinimumIntervalMs)
        return false;

    mLastPressTimeMs = timeNowMs;
    return true;
}