add_library(loader STATIC)
add_library(cms::loader ALIAS loader)

target_sources(loader
    PRIVATE
        loader.cpp
    PUBLIC
        loader.hpp
)

target_link_libraries(loader
    PUBLIC
        libs::boost
        cms::modules
)