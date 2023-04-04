set(NAME Display)
enable_language(C CXX)

set(SOURCES
        UgfxWrapper.cpp
        UgfxWrapper.h
        WeightDisplayItem.cpp
        WeightDisplayItem.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC
        Interfaces
        Terminal
        Types
        Ugfx)