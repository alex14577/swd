add_library(invoker STATIC)
add_library(libs::invoker ALIAS invoker)

target_sources(invoker
    PRIVATE
        invoker.cpp
    PUBLIC
        invoker.hpp
    INTERFACE
)

target_link_libraries(invoker
    PUBLIC
        libs::command
    INTERFACE
        hw7::meta
)
