set(NAME Tests.Time)

set(SOURCES
        tests.BrewTimer.cpp
        tests.TimeCommand.cpp
        tests.TimerAutoStart.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers.Doubles
        HalWrapper.Doubles
        Terminal.Doubles
        Time
        Time.Doubles
        Weight.Doubles
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})