add_library(commands STATIC)

target_sources(commands
    PRIVATE
        burn_fuel.cpp
        check_fuel.cpp
        move.cpp
        rotate.cpp
    PUBLIC
        burn_fuel.cpp
        check_fuel.hpp
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