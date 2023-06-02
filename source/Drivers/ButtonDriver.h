#pragma once

#include "ButtonDriverInterface.h"
#include "ButtonPressCallbackInterface.h"
#include "ExternalInterruptCallbackRegisterableInterface.h"
#include "GpioInterface.h"
#include "TerminalInterface.h"
#include "TimeInterface.h"

#include <cstddef>

namespace coffeescales::drivers
{

class ButtonDriver :
    public ButtonDriverInterface,
    public halwrapper::ExternalInterruptCallbackInterface
{
  public:
    ButtonDriver(buttons::Button button, halwrapper::GpioInterface& buttonGpio,
        halwrapper::ExternalInterruptCallbackRegisterableInterface& interruptTimer,
        halwrapper::TimeInterface& time);
    ~ButtonDriver() = default;
    void Init();
    void RegisterCallback(ButtonPressCallbackInterface* callback) override;
    void OnExternalInterrupt() override;

    static constexpr uint32_t MinimumOnTimeMs = 10;
    static constexpr size_t MaxCallbacks = 8;

  private:
    bool Debounce();

    const buttons::Button mButton;
    halwrapper::GpioInterface& mButtonGpio;
    halwrapper::ExternalInterruptCallbackRegisterableInterface& mInterruptTimer;
    halwrapper::TimeInterface& mTime;
    const size_t MinimumIntervalMs;

    ButtonPressCallbackInterface* mCallbacks[MaxCallbacks] {0};
    size_t mCallbackCount = 0;

    uint32_t mOnTimeMs = 0;
    uint32_t mTickMs = 0;
    uint32_t mLastPressTimeMs = 0;
    bool mButtonHeld = false;
};

}