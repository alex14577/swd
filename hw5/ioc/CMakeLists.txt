add_library(ioc STATIC)

target_sources(ioc
    PRIVATE
        ioc.cpp
    PUBLIC
    INTERFACE
        ioc.hpp
        command.hpp
    
)

target_link_libraries(ioc 
    PRIVATE
    PUBLIC
    INTERFACE
        hw5::meta
)