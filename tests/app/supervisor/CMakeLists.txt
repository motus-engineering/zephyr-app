cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(unit)

target_include_directories(app PUBLIC .)

target_sources(app
    PRIVATE
        main.c
        # Add tests here
        test_supervisor.c
)
target_compile_options(app PUBLIC --coverage -fprofile-abs-path)
target_link_options(app PUBLIC --coverage)

string(REPLACE "tests/" "" module_dir_path ${PROJECT_SOURCE_DIR})
add_subdirectory(${module_dir_path} "/workdir/build/tests")

# Add any dependent application include directories
# target_include_directories(app PUBLIC 
#     ${module_dir_path}/../mbif
# )
