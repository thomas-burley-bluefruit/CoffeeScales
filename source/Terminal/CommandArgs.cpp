
#include "CommandArgs.h"
#include <cstring>

using namespace ::coffeescales::terminal;

bool CommandArgs::ArgIs(size_t index, const char* value) const
{
    return Count > index && strncmp(value, Arguments[index].data(), MaxArgLength) == 0;
}

bool CommandArgs::Arg0Is(const char* value) const
{
    return ArgIs(0, value);
}

bool CommandArgs::Arg1Is(const char* value) const
{
    return ArgIs(1, value);
}

bool CommandArgs::Arg2Is(const char* value) const
{
    return ArgIs(2, value);
}

bool CommandArgs::Arg3Is(const char* value) const
{
    return ArgIs(3, value);
}

bool CommandArgs::Arg4Is(const char* value) const
{
    return ArgIs(4, value);
}

bool CommandArgs::Arg5Is(const char* value) const
{
    return ArgIs(5, value);
}

bool CommandArgs::Arg6Is(const char* value) const
{
    return ArgIs(6, value);
}
