#pragma once

#include "ButtonDriverInterface.h"
#include "ButtonPressCallbackInterface.h"
#include "ButtonGpioInterface.h"
#include "SystemInterface.h"

#include <cstddef>

namespace coffeescales::drivers
{

class ButtonDriver
        : public ButtonDriverInterface, public halwrapper::ExternalInterruptCallbackInterface
{
public:
    ButtonDriver(buttons::Button button, halwrapper::ButtonGpioInterface &buttonGpio,
                 halwrapper::SystemInterface &system);
    ~ButtonDriver() = default;
    void Init();
    void RegisterCallback(ButtonPressCallbackInterface *callback) override;
    void OnExternalInterrupt() override;

private:
    bool Debounce();

    const buttons::Button mButton;
    halwrapper::ButtonGpioInterface &mButtonGpio;
    halwrapper::SystemInterface &mSystem;
    ButtonPressCallbackInterface *mCallback = nullptr;

    const size_t MinimumIntervalMs;
    size_t mLastPressTimeMs = 0;
};

}