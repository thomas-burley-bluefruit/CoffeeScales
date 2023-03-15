#include "AdcSpy.h"

using namespace coffeescales::drivers;

bool AdcSpy::Read(int32_t &value) const
{
    ReadCallCount++;
    value = ReadValue;
    return ReadSuccess;
}

uint32_t AdcSpy::MaxValue() const
{
    return MaxAdcValue;
}
