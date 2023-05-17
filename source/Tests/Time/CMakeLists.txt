set(NAME Tests.Time)

set(SOURCES
        tests.BrewTimer.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        HalWrapper.Doubles
        Time
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})