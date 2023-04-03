cmake_minimum_required(VERSION 3.15.3)

project(CoffeeScales)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (FIRMWARE)
    include(firmware.cmake)
endif ()

if (TESTING)
    include(testing.cmake)
endif ()

add_subdirectory(source/Drivers)
add_subdirectory(source/Interfaces)
add_subdirectory(source/Terminal)
add_subdirectory(source/Types)
add_subdirectory(source/Weight)
