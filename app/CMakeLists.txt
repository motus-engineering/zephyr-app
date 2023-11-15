# Application build
target_include_directories(app
    PUBLIC
        ./
)

target_sources(app
    PRIVATE
        main.c
)

add_subdirectory(supervisor)

# Debug build options
if (CONFIG_SHELL) 
    add_subdirectory(cli)
endif ()
