add_library(utils INTERFACE)

target_sources(utils
    PUBLIC
        convert.hpp
        type_index.hpp
)

target_link_libraries(utils
    INTERFACE
        hw4::meta
)