#include "Terminal.h"
#include <cstdint>
#include <string.h>

using namespace ::halwrapper;
using namespace ::terminal;

Terminal::Terminal(const UartInterface& uart) : mUart(uart)
{
}

void Terminal::TextOut(const char *text) const
{
    const auto length = strlen(text);
    const auto txData = reinterpret_cast<const uint8_t *>(text);
    mUart.Transmit(txData, length);
}
