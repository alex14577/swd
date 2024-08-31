add_library(commands STATIC)

target_sources(commands
    PRIVATE
        command.cpp
        retry.cpp
        retry_second.cpp
        throw_cmd.cpp
        write_log.cpp
    PUBLIC
        retry.hpp
        retry_second.hpp
        throw_cmd.hpp
        write_log.hpp
    INTERFACE
        command.hpp
)

target_link_libraries(commands 
    PRIVATE
        logger
    INTERFACE
        hw3::meta
)