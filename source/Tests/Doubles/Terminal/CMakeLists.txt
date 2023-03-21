set(NAME Terminal.Doubles)

enable_language(C CXX)

set(SOURCES
        TerminalCallbackSpy.cpp
        TerminalCallbackSpy.h
        TerminalSpy.cpp
        TerminalSpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Interfaces
        Terminal)
