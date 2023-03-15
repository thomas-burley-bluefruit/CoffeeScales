set(NAME Weight.Doubles)

enable_language(C CXX)

set(SOURCES
        WeightReadingCallbackSpy.cpp
        WeightReadingCallbackSpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Interfaces)
