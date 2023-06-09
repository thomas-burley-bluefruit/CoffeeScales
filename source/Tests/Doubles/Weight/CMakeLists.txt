set(NAME Weight.Doubles)

enable_language(C CXX)

set(SOURCES
        PourRateUpdateCallbackSpy.cpp
        PourRateUpdateCallbackSpy.h
        PourRateSpy.cpp
        PourRateSpy.h
        ScalesSpy.cpp
        ScalesSpy.h
        ScalesMemoryItemSpy.cpp
        ScalesMemoryItemSpy.h
        WeightReadingCallbackSpy.cpp
        WeightReadingCallbackSpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Interfaces
        Terminal)
