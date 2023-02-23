set(NAME Application)
enable_language(C CXX)

set(SOURCES
    Application.cpp
    Application.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_compile_options(${NAME} PRIVATE
        -mcpu=cortex-m4
        -mfloat-abi=hard
)
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
    Terminal
    STM32L4)