#pragma once

#include "ExternalInterruptCallbackInterface.h"
#include "GpioInterface.h"
#include "stm32l4xx_hal.h"

#include <cstdint>

namespace coffeescales::halwrapper
{

class ButtonGpio final : public GpioInterface
{
  public:
    ButtonGpio(GPIO_TypeDef* const port, const uint32_t pin);
    void Init();
    GpioPinState GetPinState() const override;

    void SetPinState(GpioPinState state) {}

  private:
    GPIO_TypeDef* const mPort;
    const uint32_t mPin;
};

}
