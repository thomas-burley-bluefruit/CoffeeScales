#pragma once

#include <cstdint>

namespace coffeescales::halwrapper
{

class DelayTimer
{
public:
    void Init();

protected:
    void ResetCounter();
    uint16_t GetCounter();

private:
    void ErrorHandler();
};

}