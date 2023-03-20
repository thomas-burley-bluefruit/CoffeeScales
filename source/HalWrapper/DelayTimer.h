#pragma once

#include <cstdint>

namespace coffeescales::halwrapper
{

class DelayTimer
{
public:
    void Init();

protected:
    static void ResetCounter();
    static uint16_t GetCounter();

private:
    static void ErrorHandler();
};

}