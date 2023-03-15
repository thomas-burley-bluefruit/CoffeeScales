#include "TerminalCallbackSpy.h"

using namespace ::coffeescales::terminal;

bool TerminalCallbackSpy::TerminalCommand(CommandArgs &args)
{
    CallbackArgs = args;
    CallbackCount++;
    return true;
}

const char* TerminalCallbackSpy::CommandName() const
{
    return CommandNameValue;
}
