#include "TerminalCommandTest.h"

using namespace ::coffeescales::terminal;

TerminalCommandTest::TerminalCommandTest(TerminalInterface &terminal) : mTerminal(terminal)
{
    mTerminal.RegisterCommandHandler(this);
}

bool TerminalCommandTest::Callback(CommandArgs &args)
{
    mTerminal.TextOut("Command received\n");
    return true;
}

const char *TerminalCommandTest::CommandName() const
{
    return "test";
}
