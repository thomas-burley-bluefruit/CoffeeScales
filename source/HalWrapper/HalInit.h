#pragma once

namespace halwrapper
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