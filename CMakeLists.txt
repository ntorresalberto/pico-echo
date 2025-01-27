cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-projects)

pico_sdk_init()

add_executable(pico_echo
  main.c
)

target_link_libraries(pico_echo pico_stdlib pico_multicore pico_rand)

pico_enable_stdio_usb(pico_echo 1)
pico_enable_stdio_uart(pico_echo 0)

pico_add_extra_outputs(pico_echo)
