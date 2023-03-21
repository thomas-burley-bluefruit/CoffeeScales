set(NAME HalWrapper.Doubles)

enable_language(C CXX)

set(SOURCES
        SystemMock.cpp
        SystemMock.h
        UartSpy.cpp
        UartSpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers
        Interfaces
        Types)
