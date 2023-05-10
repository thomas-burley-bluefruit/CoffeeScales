set(NAME Interfaces)
enable_language(C CXX)

set(SOURCES
        AdcDriverInterface.h
        ButtonGpioInterface.h
        DisplayInterface.h
        DisplayItemInterface.h
        GpioInterface.h
        GpioInterruptCallbackInterface.h
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