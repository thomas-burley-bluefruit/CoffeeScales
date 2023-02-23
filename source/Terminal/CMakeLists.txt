set(NAME Terminal)
enable_language(C CXX)

set(SOURCES
    Terminal.cpp
    Terminal.h
    TerminalInterface.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})