set(NAME Drivers.Doubles)

enable_language(C CXX)

set(SOURCES
        AdcSpy.cpp
        AdcSpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Interfaces)
