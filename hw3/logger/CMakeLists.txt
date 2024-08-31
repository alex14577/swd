add_library(logger STATIC)

target_sources(logger
    PRIVATE
        logger.cpp
    PUBLIC
        logger.hpp
    INTERFACE
        iface.hpp
)

target_link_libraries(logger 
    PRIVATE
    INTERFACE
        hw3::meta
)