target_include_directories(app
    PUBLIC
        ./
)

target_sources(app
    PRIVATE
        led.c
)
