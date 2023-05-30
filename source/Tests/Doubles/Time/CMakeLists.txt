set(NAME Time.Doubles)

enable_language(C CXX)

set(SOURCES
        BrewTimerSpy.cpp
        BrewTimerSpy.h
        TimerAutoStartCallbackSpy.cpp
        TimerAutoStartCallbackSpy.h
        TimerIncrementCallbackSpy.cpp
        TimerIncrementCallbackSpy.h
)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers
        Interfaces
        Types)
