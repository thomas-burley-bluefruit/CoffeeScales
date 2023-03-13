#pragma once

namespace coffeescales::halwrapper
{

class HalInit
{
public:
    void Init();

private:
    void ErrorHandler();
    void SystemClockConfig();
    void MxGpioInit();
};

}