cmake_minimum_required(VERSION 3.22)

add_library(ssd1306 STATIC)

target_sources(ssd1306
    PRIVATE
        src/ssd1306.c
)

target_include_directories(ssd1306 PUBLIC include)
target_link_libraries(ssd1306 PUBLIC stm32cubemx)
