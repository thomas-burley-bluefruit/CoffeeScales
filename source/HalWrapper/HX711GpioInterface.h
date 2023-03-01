#pragma once

namespace halwrapper
{

class HX711GpioInterface
{
public:
    ~HX711GpioInterface() = default;
    virtual bool GetDataPinState() const = 0;
    virtual void SetClockPin(const bool state) = 0;
};

}