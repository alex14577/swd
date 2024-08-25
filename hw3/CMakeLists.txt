include(hw3.cmake)

add_subdirectory(app)
add_subdirectory(commands)
add_subdirectory(exceptions)
add_subdirectory(logger)
add_subdirectory(queue)
add_subdirectory(test)

add_library(hw3 INTERFACE)

target_sources(hw3
    PRIVATE
    PUBLIC
)

target_link_libraries(hw3
    INTERFACE
        hw3::meta
        commands
        command_queue
)
