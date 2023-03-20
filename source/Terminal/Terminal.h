#pragma once

#include <array>
#include <cstddef>
#include "TerminalInterface.h"
#include "UartInterface.h"

namespace coffeescales::terminal
{

class Terminal : public TerminalInterface, public halwrapper::ReceiveInterruptCallbackInterface
{
public:
    explicit Terminal(halwrapper::UartInterface& uart);
    void Start();
    void Task();
    void TextOut(const char* text) const override;
    void OnReceiveInterrupt(uint8_t byte) override;
    void OnReceiveError() override;
    bool RegisterCommandHandler(TerminalCallbackInterface* callback) override;

    static constexpr size_t TerminalBufferSize = 256u;
    static constexpr size_t MaxCommandHandlers = 32;

private:
    void ProcessCommand();
    void ExtractCommandName(char* buf, size_t& argsStartPos);
    CommandArgs ExtractArgs(size_t startPos);

    bool mCommandReceived = false;
    size_t mCommandHandlerCount = 0;
    std::array<TerminalCallbackInterface*, MaxCommandHandlers> mCommandHandlers {nullptr};
    halwrapper::UartInterface& mUart;
    std::array<char, TerminalBufferSize> mCommandBuffer{};
    size_t mCommandCharacterCount = 0;
    static constexpr char CommandTerminator = '\n';
};

}