set(NAME Display)
enable_language(C CXX)

set(SOURCES
        board_SSD1306.cpp
        board_SSD1306.h
        UgfxTick.cpp
        ugfx/src/gfx_mk.c)

set(SSD1306_DRIVER_DIR ugfx/drivers/gdisp/SSD1306)

set(SSD1306_DRIVER_SOURCES
        ${SSD1306_DRIVER_DIR}/gdisp_lld_SSD1306.c
        ${SSD1306_DRIVER_DIR}/gdisp_lld_config.h
        ${SSD1306_DRIVER_DIR}/SSD1306.h
        )

set(INCLUDES . ugfx ${SSD1306_DRIVER_DIR})

add_library(${NAME} STATIC ${SOURCES} ${SSD1306_DRIVER_SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC HalWrapper)