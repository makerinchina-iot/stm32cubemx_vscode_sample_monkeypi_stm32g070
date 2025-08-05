cmake_minimum_required(VERSION 3.22)

add_library(utils STATIC)

target_sources(utils
    PRIVATE
        src/mnumber.c
)

target_include_directories(utils PUBLIC include port)
# target_link_libraries(utils PUBLIC stm32cubemx)
