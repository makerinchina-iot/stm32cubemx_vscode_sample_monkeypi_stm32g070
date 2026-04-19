cmake_minimum_required(VERSION 3.22)

add_library(tft STATIC)

target_sources(tft
    PRIVATE
        port/tft_port.c
        src/gc9a01.c
)

target_include_directories(tft PUBLIC include port)
target_link_libraries(tft PUBLIC stm32cubemx)
