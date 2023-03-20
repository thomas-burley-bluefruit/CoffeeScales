set(NAME HalWrapper)
enable_language(C CXX)

set(SOURCES
        Time.cpp
        Time.h
        DelayTimer.cpp
        DelayTimer.h
        HalErrorHandler.c
        HalErrorHandler.h
        HalInit.cpp
        HalInit.h
        HX711Gpio.cpp
        HX711Gpio.h
        System.cpp
        System.h
        Uart.cpp
        Uart.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC Interfaces STM32L4 Types)