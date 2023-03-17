set(NAME Interfaces)
enable_language(C CXX)

set(SOURCES
        TimeInterface.h
        AdcDriverInterface.h
        GpioInterface.h
        ReceiveInterruptCallbackInterface.h
        SpiInterface.h
        SystemInterface.h
        TerminalCallbackInterface.h
        TerminalInterface.h
        UartInterface.h)

set(INCLUDES .)

add_library(${NAME} INTERFACE ${SOURCES})
target_include_directories(${NAME} INTERFACE ${INCLUDES})