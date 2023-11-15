cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT ${CMAKE_SOURCE_DIR})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(zephyr-app)

# Application build
target_include_directories(app
    PUBLIC
        ./
)

target_sources(app
    PRIVATE
        main.c
)

add_subdirectory(actor)
add_subdirectory(event)
add_subdirectory(hsm)
add_subdirectory(supervisor)

add_subdirectory(led)
add_subdirectory(button)

# Debug build options
if (CONFIG_SHELL) 
    add_subdirectory(cli)
endif ()
