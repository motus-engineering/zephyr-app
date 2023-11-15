cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT ${CMAKE_SOURCE_DIR})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(zephyr-app)

# Add application source files
add_subdirectory(app)
