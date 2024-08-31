add_library(command_queue STATIC)

target_sources(command_queue
    PRIVATE
        queue.cpp
    PUBLIC
        queue.hpp
    INTERFACE
        iface.hpp
)

target_link_libraries(command_queue 
    PRIVATE
        commands
    INTERFACE
        hw3::meta
)