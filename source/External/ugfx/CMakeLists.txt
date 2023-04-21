set(NAME Ugfx)
enable_language(C CXX)

set(SOURCES
        SSD1322/board_SSD1322.cpp
        SSD1322/board_SSD1322.h
        SSD1322/gdisp_lld_SSD1322.c
        UgfxTick.cpp
        ugfx/src/gfx_mk.c
        UgfxUtilities.h
        UgfxWrapper.cpp
        UgfxWrapper.h)

set(SSD1322_DRIVER_DIR ugfx/drivers/gdisp/SSD1322)
set(SSD1322_DRIVER_SOURCES
        ${SSD1322_DRIVER_DIR}/gdisp_lld_config.h
        ${SSD1322_DRIVER_DIR}/SSD1322.h
        )

set(INCLUDES . ugfx ${SSD1322_DRIVER_DIR})

add_library(${NAME} STATIC ${SOURCES} ${SSD1322_DRIVER_SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC HalWrapper Types)