set(NAME Tests.Drivers)

set(SOURCES
        tests.ButtonDriver.cpp
        tests.EepromDriver.cpp
        tests.HX711Driver.cpp
        tests.Utilities.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers
        Drivers.Doubles
        HalWrapper.Doubles
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})
