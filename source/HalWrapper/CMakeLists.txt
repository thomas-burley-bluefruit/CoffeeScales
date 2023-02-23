set(NAME HalWrapper)
enable_language(C CXX)

set(SOURCES
    HX711.cpp
    HX711.h
    Uart.cpp
    Uart.h
    UartInterface.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_compile_options(${NAME} PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -fdata-sections
    -ffunction-sections
    -Wall
    $<$<CONFIG:Debug>:-Og>
    -fno-exceptions
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)

target_compile_definitions(${NAME} PRIVATE
    -DSTM32L432xx
)

target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC STM32L4 Terminal)