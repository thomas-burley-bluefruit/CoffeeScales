#include "ScalesCommand.h"
#include "GenericTerminalCommands.h"

using namespace ::coffeescales::terminal;
using namespace ::coffeescales::weight;

ScalesCommand::ScalesCommand(ScalesInterface &scales,
                             TerminalInterface &terminal) : mScales(scales), mTerminal(terminal)
{
    mTerminal.RegisterCommandHandler(this);
}

bool ScalesCommand::TerminalCommand(CommandArgs &args)
{
    if (args.Arg0Is(ScalesTerminalCommands::Calibrate))
    {
        if (args.Count == 1)
        {
            mScales.CalibrateInit();
            return true;
        }

        if (args.Count == 2 && args.Arg1Is(ScalesTerminalCommands::Set))
        {
            mScales.CalibrateSet();
            return true;
        }
    }

    if (args.Arg0Is(ScalesTerminalCommands::Adc))
    {
        if (args.Count != 2)
            return false;

        if (args.Arg1Is(GenericTerminalCommands::On))
        {
            mScales.AdcDebugPrint(true);
            return true;
        }

        if (args.Arg1Is(GenericTerminalCommands::Off))
        {
            mScales.AdcDebugPrint(false);
            return true;
        }
    }

    if (args.Arg0Is(ScalesTerminalCommands::Weight))
    {
        if (args.Count != 2)
            return false;

        if (args.Arg1Is(GenericTerminalCommands::On))
        {
            mScales.WeightDebugPrint(true);
            return true;
        }

        if (args.Arg1Is(GenericTerminalCommands::Off))
        {
            mScales.WeightDebugPrint(false);
            return true;
        }
    }

    if (args.Count == 1 && args.Arg0Is(ScalesTerminalCommands::Tare))
    {
        mScales.TareInit();
        return true;
    }

    return false;
}
