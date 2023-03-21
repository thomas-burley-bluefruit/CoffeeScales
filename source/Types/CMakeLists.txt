set(NAME Types)
enable_language(C CXX)

set(SOURCES
        Types.h)

set(INCLUDES .)

add_library(${NAME} INTERFACE ${SOURCES})
target_include_directories(${NAME} INTERFACE ${INCLUDES})
