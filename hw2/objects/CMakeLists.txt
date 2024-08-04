add_library(objects STATIC)

target_sources(objects
    PRIVATE
        factory.cpp
        movable.cpp
        object.cpp
        rotatable.cpp
    PUBLIC
        factory.hpp
        movable.hpp
        object.hpp
        rotatable.hpp
)

target_link_libraries(objects 
    INTERFACE
        movement::meta
    PUBLIC
        properties
)