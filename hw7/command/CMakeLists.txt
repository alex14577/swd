add_library(command STATIC)
add_library(libs::command ALIAS command)

target_sources(command
    PRIVATE
        commands.cpp        
    PUBLIC

    INTERFACE
        command.hpp
)

target_link_libraries(command
    INTERFACE
        hw7::meta
        libs::invoker
)
