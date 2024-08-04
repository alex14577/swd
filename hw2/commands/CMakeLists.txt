add_library(commands STATIC)

target_sources(commands
    PRIVATE
        move.cpp
        rotate.cpp
    PUBLIC
        move.hpp
        rotate.hpp
    INTERFACE
        command.hpp
)

target_link_libraries(commands 
    PRIVATE
        properties
    INTERFACE
        utils
)