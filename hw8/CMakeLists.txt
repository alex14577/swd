include(hw8.cmake)
add_subdirectory(command)
add_subdirectory(object)
add_subdirectory(transport)


add_library(hw8 INTERFACE)

target_link_libraries(hw8
    INTERFACE
        hw8::meta
)

add_subdirectory(test)