set(NAME HalWrapper.Doubles)

enable_language(C CXX)

set(SOURCES
        ButtonGpioSpy.cpp
        ButtonGpioSpy.h
        SystemMock.cpp
        SystemMock.h
        SpiSpy.cpp
        SpiSpy.h
        UartSpy.cpp
        UartSpy.h
        )

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers
        Interfaces
        Types)
