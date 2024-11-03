add_library(transport INTERFACE)
add_library(cms::transport ALIAS transport)

target_sources(transport 
    INTERFACE
        queue.hpp
)
