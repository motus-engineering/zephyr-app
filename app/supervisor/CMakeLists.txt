target_include_directories(app
    PUBLIC
        ./
)

target_sources(app
    PRIVATE
        supervisor.c
        fault_state.c
        init_state.c
        panic_state.c
        root_state.c
        supervise_state.c
)
