add_library(modules INTERFACE)
add_library(cms::modules ALIAS modules)

target_sources(modules
    INTERFACE
        module.hpp
)

target_link_libraries(modules
    INTERFACE
        cms::meta
)

add_subdirectory(module1)
add_subdirectory(in)
add_subdirectory(out)