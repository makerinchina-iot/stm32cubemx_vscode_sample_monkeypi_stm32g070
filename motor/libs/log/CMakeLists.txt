cmake_minimum_required(VERSION 3.22)

add_library(log STATIC)

target_sources(log
    PRIVATE
        src/log.c
        src/log2rtt.c
)

target_include_directories(log PUBLIC include)
target_link_libraries(log PUBLIC segger_rtt stm32cubemx)
