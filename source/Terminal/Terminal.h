#include <cstddef>
#include "TerminalInterface.h"

namespace terminal
{

class Terminal : public TerminalInterface
{
public:
    Terminal();
    void Init();
    void Transmit(const char* txData, size_t size) override;
};

}