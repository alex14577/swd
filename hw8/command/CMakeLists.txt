add_library(commands STATIC)
add_library(libs::commands ALIAS commands)

target_sources(commands
    PRIVATE
        set_speed.cpp
    PUBLIC
        set_speed.hpp
        command.hpp
)

target_link_libraries(commands
    PUBLIC
        libs::objects
    INTERFACE
        hw8::meta
)
