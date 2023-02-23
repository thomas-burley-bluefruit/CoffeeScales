#include <cstddef>
#include "TerminalInterface.h"
#include "UartInterface.h"

namespace terminal
{

class Terminal : public TerminalInterface
{
public:
    Terminal(const halwrapper::UartInterface& uart);
    void TextOut(const char* text) const override;

private:
    const halwrapper::UartInterface& mUart;
};

}