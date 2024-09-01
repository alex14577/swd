add_library(objects STATIC)

target_sources(objects
    PRIVATE
        factory.cpp
        movable.cpp
        object.cpp
        rotatable.cpp
        with_fuel.cpp
    PUBLIC
        factory.hpp
        movable.hpp
        object.hpp
        rotatable.hpp
        with_fuel.hpp
)

target_link_libraries(objects 
    INTERFACE
    PUBLIC
        properties
)