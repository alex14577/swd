add_library(macro_command STATIC)

target_sources(macro_command
    PRIVATE
        factory.cpp
        macro_command.cpp
    PUBLIC
        factory.hpp
        macro_command.hpp
    INTERFACE

)

target_link_libraries(macro_command 
    PRIVATE
        commands
    PUBLIC

    INTERFACE
        hw4::meta
)