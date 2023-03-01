#pragma once
#include "TerminalInterface.h"
#include "HX711GpioInterface.h"
#include "DelayInterface.h"

namespace halwrapper
{

class HX711Gpio : public HX711GpioInterface
{
public:
    HX711Gpio(const terminal::TerminalInterface& terminal);
    ~HX711Gpio() = default;
    bool GetDataPinState() const override;
    void SetClockPin(const bool state) override;

private:
    const terminal::TerminalInterface& mTerminal;
};

}