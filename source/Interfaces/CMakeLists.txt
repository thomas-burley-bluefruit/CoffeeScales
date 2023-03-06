set(NAME Interfaces)
enable_language(C CXX)

set(SOURCES
        DelayInterface.h
        HX711DriverInterface.h
        GpioInterface.h
        SystemInterface.h
        TerminalInterface.h
        UartInterface.h)

set(INCLUDES .)

add_library(${NAME} INTERFACE ${SOURCES})
target_include_directories(${NAME} INTERFACE ${INCLUDES})