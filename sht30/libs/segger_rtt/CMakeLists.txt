cmake_minimum_required(VERSION 3.22)

add_library(segger_rtt STATIC)

target_sources(segger_rtt
    PRIVATE
        src/SEGGER_RTT.c
        src/SEGGER_RTT_printf.c
)

target_include_directories(segger_rtt PUBLIC include)
target_link_libraries(segger_rtt PUBLIC stm32cubemx)
