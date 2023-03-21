#pragma once

#include <array>
#include <cstddef>

namespace coffeescales::terminal
{

struct CommandArgs
{
    static constexpr size_t MaxArgLength = 32u;
    static constexpr size_t MaxArguments = 7u;

    size_t Count = 0;
    std::array<std::array<char, MaxArgLength>, MaxArguments> Arguments{};

    bool ArgIs(size_t index, const char *value) const;
    bool Arg0Is(const char *value) const;
    bool Arg1Is(const char *value) const;
    bool Arg2Is(const char *value) const;
    bool Arg3Is(const char *value) const;
    bool Arg4Is(const char *value) const;
    bool Arg5Is(const char *value) const;
    bool Arg6Is(const char *value) const;
};

}
