#include "TerminalCommandTest.h"

using namespace terminal;

TerminalCommandTest::TerminalCommandTest(terminal::TerminalInterface &terminal) : mTerminal(terminal)
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
