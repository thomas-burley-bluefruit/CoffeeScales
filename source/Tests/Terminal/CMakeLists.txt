set(NAME Tests.Terminal)

set(SOURCES
        tests.Terminal.cpp)

set(INCLUDES .)

enable_testing()
add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Drivers
        HalWrapper.Doubles
        Terminal.Doubles
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})