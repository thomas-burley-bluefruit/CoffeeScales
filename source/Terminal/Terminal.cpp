#include "Terminal.h"
#include <cstdint>
#include <cstring>

using namespace ::coffeescales::halwrapper;
using namespace ::coffeescales::terminal;

Terminal::Terminal(UartInterface &uart) : mUart(uart)
{
    mCommandBuffer.fill('\0');
}

void Terminal::Start()
{
    mUart.Init();
    mUart.SetCallback(this);
}

void Terminal::Task()
{
    if (mCommandReceived)
        ProcessCommand();
}

void Terminal::ProcessCommand()
{
    char commandName[TerminalCallbackInterface::MaxCommandNameLength]{0};
    size_t argsStartPos = 0;
    ExtractCommandName(commandName, argsStartPos);

    auto args = ExtractArgs(argsStartPos);

    for (auto handler: mCommandHandlers)
    {
        if (handler == nullptr)
            continue;

        if (strncmp(handler->CommandName(), commandName,
                    TerminalCallbackInterface::MaxCommandNameLength) == 0)
        {
            handler->TerminalCommand(args);
            mCommandReceived = false;
            return;
        }
    }
}

void Terminal::ExtractCommandName(char *buf, size_t &argsStartPos)
{
    size_t commandNameLength = 0;

    for (size_t i = 0; i < mCommandBuffer.size(); ++i)
    {
        auto &ch = mCommandBuffer[i];

        if (ch == '\0')
            break;

        if (ch == ' ')
        {
            argsStartPos = i + 1;
            break;
        }

        commandNameLength++;
    }

    strncpy(buf, mCommandBuffer.data(), commandNameLength);
}

CommandArgs Terminal::ExtractArgs(size_t startPos)
{
    CommandArgs args{0};

    if (startPos == 0)
        return args;

    const char *currentArgStart = &mCommandBuffer[startPos];

    for (size_t i = startPos; i < mCommandBuffer.size(); ++i)
    {
        auto &ch = mCommandBuffer[i];

        if (ch == ' ' || ch == '\0')
        {
            if (*currentArgStart != ' ')
            {
                strncpy(args.Arguments[args.Count].data(),
                        currentArgStart,
                        &ch - currentArgStart);

                args.Count++;
            }
            currentArgStart = &ch + 1;
        }

        if (ch == '\0' || args.Count >= CommandArgs::MaxArguments)
            break;
    }
    return args;
}

void Terminal::TextOut(const char *text) const
{
    const auto length = strlen(text);
    const auto txData = reinterpret_cast<const uint8_t *>(text);
    mUart.Transmit(txData, length);
}

void Terminal::OnReceiveInterrupt(const uint8_t byte)
{
    char character = static_cast<char>(byte);
    if (character == CommandTerminator)
    {
        mCommandBuffer[mCommandCharacterCount] = '\0';
        mCommandCharacterCount = 0;
        mCommandReceived = true;
        return;
    }

    if (mCommandCharacterCount >= TerminalBufferSize)
        return;
    mCommandBuffer[mCommandCharacterCount++] = character;
}

void Terminal::OnReceiveError()
{
}

bool Terminal::RegisterCommandHandler(TerminalCallbackInterface *callback)
{
    auto commandNameLen = strlen(callback->CommandName());
    if (commandNameLen > TerminalCallbackInterface::MaxCommandNameLength)
        return false;

    if (mCommandHandlerCount >= MaxCommandHandlers)
        return false;

    mCommandHandlers[mCommandHandlerCount++] = callback;
    return true;
}
