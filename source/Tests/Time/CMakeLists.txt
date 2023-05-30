set(NAME Tests.Time)

set(SOURCES
        tests.BrewTimer.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers.Doubles        
        HalWrapper.Doubles
        Time
        Time.Doubles
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})