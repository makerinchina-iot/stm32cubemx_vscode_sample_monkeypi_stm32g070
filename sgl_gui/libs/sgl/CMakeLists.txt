cmake_minimum_required(VERSION 3.22)

add_library(sgl STATIC)

# set(SGL_HEAP_ALGO lwmem)

file(GLOB SGL_CORE_SOURCES source/core/*.c)
file(GLOB SGL_DRAW_SOURCES source/draw/*.c)
file(GLOB SGL_FONTS_SOURCES source/fonts/*.c)
file(GLOB SGL_MM_SOURCES source/mm/lwmem/*.c)
file(GLOB SGL_WIDGETS_SOURCES source/widgets/*/*.c)

set(SGL_SOURCES
    ${SGL_CORE_SOURCES}
    ${SGL_DRAW_SOURCES}
    ${SGL_FONTS_SOURCES}
    ${SGL_MM_SOURCES}
    ${SGL_WIDGETS_SOURCES}
)

target_sources(sgl
    PRIVATE
        ${SGL_SOURCES}
)

target_include_directories(sgl PUBLIC source/include source)
target_link_libraries(sgl PUBLIC stm32cubemx)
