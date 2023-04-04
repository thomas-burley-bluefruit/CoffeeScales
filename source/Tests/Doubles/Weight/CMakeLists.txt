set(NAME Weight.Doubles)

enable_language(C CXX)

set(SOURCES
        ScalesSpy.cpp
        ScalesSpy.h
        WeightReadingCallbackSpy.cpp
        WeightReadingCallbackSpy.h
        ScalesMemoryItemSpy.cpp
        ScalesMemoryItemSpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Interfaces
        Terminal)
