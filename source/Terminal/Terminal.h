#include <cstddef>
#include "TerminalInterface.h"
#include "UartInterface.h"

namespace terminal
{

class Terminal : public TerminalInterface
{
public:
    Terminal(const halwrapper::UartInterface& uart);
    void Transmit(const char* txData, size_t size) const override;

private:
    const halwrapper::UartInterface& mUart;
};

}