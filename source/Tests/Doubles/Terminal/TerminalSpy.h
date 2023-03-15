#pragma once

#include "TerminalInterface.h"
#include "Terminal.h"

namespace coffeescales::terminal
{

class TerminalSpy : public coffeescales::terminal::TerminalInterface
{
public:
    void TextOut(const char *text) const override;
    bool RegisterCommandHandler(TerminalCallbackInterface *callback) override;

    mutable bool TextOutCalled = false;
    mutable char TextOutValue[Terminal::TerminalBufferSize] {0};
};

}
