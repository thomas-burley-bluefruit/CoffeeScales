#include "HX711.h"

using namespace ::halwrapper;
using namespace ::terminal;

HX711::HX711(const TerminalInterface& terminal) : mTerminal(terminal)
{
}
