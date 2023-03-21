set(NAME Tests.Weight)

set(SOURCES
        tests.Scales.cpp
        tests.ScalesCommand.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers.Doubles
        HalWrapper.Doubles
        Terminal.Doubles
        Weight
        Weight.Doubles
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})