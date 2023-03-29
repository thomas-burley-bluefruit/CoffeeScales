set(NAME ugfx)
enable_language(C CXX)


set(SOURCES
        ugfx/src/gfx_mk.c
        UgfxTick.cpp
        gfxconf.h)

set(SSD1306_DRIVER_DIR ugfx/drivers/gdisp/SSD1306)

set(SSD1306_DRIVER_SOURCES
        ${SSD1306_DRIVER_DIR}/gdisp_lld_SSD1306.c
        ${SSD1306_DRIVER_DIR}/gdisp_lld_config.h
        ${SSD1306_DRIVER_DIR}/SSD1306.h
        )

set(INCLUDES . ugfx ${SSD1306_DRIVER_DIR} SSD1306)

add_library(${NAME} STATIC ${SSD1306_DRIVER_SOURCES} ${SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC HalWrapper)