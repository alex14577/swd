include(hw4.cmake)

add_subdirectory(macro_commands)
add_subdirectory(properties)
add_subdirectory(objects)
add_subdirectory(commands)
add_subdirectory(utils)
add_subdirectory(test)

add_library(hw4 INTERFACE)

target_sources(hw4
    PRIVATE

    PUBLIC

)

target_link_libraries(hw4
    INTERFACE
        hw4::meta
)
