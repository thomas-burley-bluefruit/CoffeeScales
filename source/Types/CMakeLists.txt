set(NAME Types)
enable_language(C CXX)

set(SOURCES
    DisplayFontSize.h
    DisplayJustify.h
    GpioPinState.h)

set(INCLUDES .)

add_library(${NAME} INTERFACE ${SOURCES})
target_include_directories(${NAME} INTERFACE ${INCLUDES})
