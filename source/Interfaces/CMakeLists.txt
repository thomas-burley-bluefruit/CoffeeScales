set(NAME Interfaces)
enable_language(C CXX)

set(SOURCES
        AdcDriverInterface.h
        DisplayGpioInterface.h
        DisplayInterface.h
        GpioInterface.h
        PersistentMemoryInterface.h
        ReceiveInterruptCallbackInterface.h
        SpiInterface.h
        SystemInterface.h
        TerminalCallbackInterface.h
        TerminalInterface.h
        TimeInterface.h
        UartInterface.h)

set(INCLUDES .)

add_library(${NAME} INTERFACE ${SOURCES})
target_include_directories(${NAME} INTERFACE ${INCLUDES})