add_library(properties STATIC)

target_sources(properties
    PRIVATE
        direction.cpp
        directions_number.cpp
        fuel.cpp
        fuel_consumption.cpp
        position.cpp
        position_angle.cpp
        static_posiotion.cpp
        velocity.cpp
        velocity_angle.cpp
    PUBLIC
        direction.hpp
        directions_number.hpp
        fuel.hpp
        fuel_consumption.hpp
        position.hpp
        static_posiotion.hpp
        position_angle.hpp
        velocity.hpp
        velocity_angle.hpp
    INTERFACE
        property.hpp
)

target_link_libraries(properties
    PUBLIC
        utils
    INTERFACE
        hw4::meta
)
