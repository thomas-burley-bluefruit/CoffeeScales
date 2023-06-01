set(NAME HalWrapper)
enable_language(C CXX)

set(SOURCES
        ButtonGpio.cpp
        ButtonGpio.h
        ButtonMapping.h
        DelayTimer.cpp
        DelayTimer.h
        DisplayGpio.cpp
        DisplayGpio.h
        HalErrorHandler.cpp
        HalErrorHandler.h
        HalInit.cpp
        HalInit.h
        HalMsp.cpp
        HalMsp.h
        HX711Gpio.cpp
        HX711Gpio.h
        InterruptTimerGpio.cpp
        InterruptTimerGpio.h
        Spi.cpp
        Spi.h
        System.cpp
        System.h
        Time.cpp
        Time.h
        Uart.cpp
        Uart.h
        )

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC Interfaces STM32L4 Types)