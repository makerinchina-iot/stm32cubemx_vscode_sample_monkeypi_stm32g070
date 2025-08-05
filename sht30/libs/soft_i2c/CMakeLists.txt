cmake_minimum_required(VERSION 3.22)

add_library(soft_i2c STATIC)

target_sources(soft_i2c
    PRIVATE
        src/soft_i2c.c
        port/soft_i2c_port.c
        src/i2c_scanner.c
)

target_include_directories(soft_i2c PUBLIC include port)
target_link_libraries(soft_i2c PUBLIC stm32cubemx)
