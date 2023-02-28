set(NAME HalWrapper)
enable_language(C CXX)

set(SOURCES
    Delay.cpp
    Delay.h
    DelayTimer.cpp
    DelayTimer.h
    HalInit.cpp
    HalInit.h
    HX711.cpp
    HX711.h
    Uart.cpp
    Uart.h
    UartInterface.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC STM32L4 Terminal)