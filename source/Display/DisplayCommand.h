#pragma once

#include "DisplayItemInterface.h"
#include "DisplayTerminalCommands.h"
#include "TerminalInterface.h"
#include "TerminalCallbackInterface.h"

namespace coffeescales::display
{

class DisplayCommand final : public terminal::TerminalCallbackInterface
{
public:
    DisplayCommand(terminal::TerminalInterface &terminal, DisplayItemInterface &weightDisplayItem);
    bool TerminalCommand(terminal::CommandArgs &args) override;

    const char *CommandName() const override
    { return DisplayTerminalCommands::CommandName; }

private:
    DisplayItemInterface &mWeightDisplayItem;
};

}
