set(NAME Display.Doubles)

enable_language(C CXX)

set(SOURCES
        DisplaySpy.cpp
        DisplaySpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Interfaces
        Types)
