#include <cstddef>
#include "TerminalInterface.h"

namespace terminal
{

    class Terminal : public TerminalInterface
    {
        void Transmit(const char* txData, size_t size) override;
    };

}