add_library(transport STATIC)
add_library(libs::transport ALIAS transport)

target_sources(transport
    PRIVATE
        queue.cpp
    PUBLIC
        builder.hpp
)

target_link_libraries(transport
    PUBLIC
        libs::command
    INTERFACE
        hw8::meta
)
