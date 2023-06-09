set(NAME Tests.Display)

set(SOURCES
        tests.DisplayCommand.cpp
        tests.DisplayManager.cpp
        tests.TimeDisplayItem.cpp
        tests.PourRateDisplayItem.cpp
        tests.WeightDisplayitem.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Display
        Display.Doubles
        Terminal.Doubles
        Time.Doubles
        Weight.Doubles
        gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})
