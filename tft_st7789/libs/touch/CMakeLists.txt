cmake_minimum_required(VERSION 3.22)

add_library(touch STATIC)

target_sources(touch
    PRIVATE
        port/touch_port.c
        src/xpt2046.c
)

target_include_directories(touch PUBLIC include port)
target_link_libraries(touch PUBLIC stm32cubemx log)
