cmake_minimum_required(VERSION 3.15.3)

project(CoffeeScales)

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(EXECUTABLE ${PROJECT_NAME}.out)

set(SOURCES
        source/STM32L4/Inc/stm32l4xx_hal_conf.h
        source/Application/main.cpp
        source/STM32L4/Src/stm32l4xx_it.c
        source/STM32L4/Src/system_stm32l4xx.c
        source/STM32L4/startup_stm32l432xx.s)

add_executable(${EXECUTABLE} ${SOURCES})

set(COMPILE_OPTIONS
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -fdata-sections
        -ffunction-sections
        -Wall
        $<$<CONFIG:Debug>:-Og>
        -fno-exceptions
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)
target_compile_options(${EXECUTABLE} PRIVATE ${COMPILE_OPTIONS})

set(COMPILE_DEFINITIONS
        -DUSE_HAL_DRIVER
        -DSTM32L432xx)
target_compile_definitions(${EXECUTABLE} PRIVATE ${COMPILE_DEFINITIONS})

set(LINK_OPTIONS
        -T${CMAKE_SOURCE_DIR}/source/STM32L4/STM32L432KCUx_FLASH.ld
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -specs=nosys.specs
        -lc
        -lm
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections)
target_link_options(${EXECUTABLE} PRIVATE ${LINK_OPTIONS})

set_target_properties(${EXECUTABLE} PROPERTIES ADDITIONAL_CLEAN_FILES
        "${PROJECT_NAME}.bin;${PROJECT_NAME}.hex;${PROJECT_NAME}.map")

add_subdirectory(source/Application)
add_subdirectory(source/HalWrapper)
add_subdirectory(source/STM32L4)
add_subdirectory(source/Terminal)

target_link_libraries(${EXECUTABLE} PUBLIC
        Application)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
