#include "TerminalCallbackSpy.h"

using namespace ::terminal;

bool TerminalCallbackSpy::Callback(CommandArgs &args)
{
    CallbackArgs = args;
    CallbackCount++;
    return true;
}

const char* TerminalCallbackSpy::CommandName() const
{
    return CommandNameValue;
}
