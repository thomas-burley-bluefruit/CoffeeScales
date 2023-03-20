#pragma once

namespace coffeescales::halwrapper
{

class HalInit
{
public:
    void Init();

private:
    static void ErrorHandler();
    void SystemClockConfig();
    static void MxGpioInit();
};

}