#include "DisplayCommand.h"
#include "GenericTerminalCommands.h"

using namespace coffeescales::display;

DisplayCommand::DisplayCommand(terminal::TerminalInterface &terminal,
                               DisplayItemInterface &weightDisplayItem) : mWeightDisplayItem(
        weightDisplayItem)
{
    terminal.RegisterCommandHandler(this);
}

bool DisplayCommand::TerminalCommand(terminal::CommandArgs &args)
{
    if (args.Arg0Is(DisplayTerminalCommands::Weight))
    {
        if (args.Count != 2)
            return false;

        if (args.Arg1Is(terminal::GenericTerminalCommands::On))
        {
            mWeightDisplayItem.DebugPrint(true);
            return true;
        }

        if (args.Arg1Is(terminal::GenericTerminalCommands::Off))
        {
            mWeightDisplayItem.DebugPrint(false);
            return true;
        }
    }
    return false;
}
