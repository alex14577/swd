include(hw2.cmake)

add_library(movement INTERFACE)

target_sources(movement
    PRIVATE
    PUBLIC
)

target_link_libraries(movement
    INTERFACE
        movement::meta
        properties
        objects
        commands
)

add_subdirectory(properties)
add_subdirectory(objects)
add_subdirectory(commands)
add_subdirectory(utils)
add_subdirectory(test)