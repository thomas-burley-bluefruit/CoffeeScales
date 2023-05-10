#pragma once

#include "GpioInterruptCallbackInterface.h"
#include "ButtonGpioInterface.h"
#include "TerminalInterface.h"
#include "SystemInterface.h"

namespace coffeescales::drivers
{

class TareButtonDriver final : public halwrapper::GpioInterruptCallbackInterface
{
public:
    TareButtonDriver(halwrapper::ButtonGpioInterface &tareButton,
                     halwrapper::SystemInterface &time,
                     terminal::TerminalInterface &terminal);
    void OnReceiveInterrupt() override;

    static constexpr size_t MinimumIntervalMs = 100;

private:
    bool Debounce();

    terminal::TerminalInterface &mTerminal;
    halwrapper::SystemInterface &mSystem;
    size_t mLastPressTimeMs = 0;
};

}
