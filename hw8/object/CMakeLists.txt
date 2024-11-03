add_library(objects INTERFACE)
add_library(libs::objects ALIAS objects)

target_sources(objects
    PRIVATE

    PUBLIC
        object.hpp
)

target_link_libraries(objects
    INTERFACE
        hw8::meta
)
