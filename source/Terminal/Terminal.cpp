#include "Terminal.h"
#include <cstdint>

using namespace ::halwrapper;
using namespace ::terminal;

Terminal::Terminal(const UartInterface& uart) : mUart(uart)
{
}

void Terminal::Transmit(const char *txData, size_t size) const
{
//    mUart.t
}
