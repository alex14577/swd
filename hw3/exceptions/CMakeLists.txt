add_library(exceptions STATIC)

target_sources(exceptions
    PRIVATE
        handler.cpp
    PUBLIC
        handler.hpp
    INTERFACE
        iface.hpp
)

target_link_libraries(exceptions 
    PRIVATE
        commands
    INTERFACE
        hw3::meta
)