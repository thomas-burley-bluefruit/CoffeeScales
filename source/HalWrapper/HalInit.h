#pragma once

namespace coffeescales::halwrapper
{

class HalInit
{
public:
    void Init();

private:
    void SystemClockConfig();
    static void MxGpioInit();
};

}