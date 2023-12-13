target_include_directories(app
    PUBLIC
        ./
)

target_sources(app
    PRIVATE
        ble_concurrent_roles.c
)