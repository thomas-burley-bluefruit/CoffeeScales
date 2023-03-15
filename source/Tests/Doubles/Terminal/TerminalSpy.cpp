#include "TerminalSpy.h"

#include <string>

using namespace ::coffeescales::terminal;

void TerminalSpy::TextOut(const char *text) const
{
    TextOutCalled = true;
    strncpy_s(TextOutValue, Terminal::TerminalBufferSize,
              text, Terminal::TerminalBufferSize);
}

bool TerminalSpy::RegisterCommandHandler(TerminalCallbackInterface *callback)
{
    return true;
}
