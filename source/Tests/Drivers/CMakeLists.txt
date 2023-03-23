set(NAME Tests.Drivers)

set(SOURCES
        tests.EepromDriver.cpp
        tests.HX711Driver.cpp
        tests.Utilities.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers
        HalWrapper.Doubles
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})
