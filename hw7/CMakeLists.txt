include(hw7.cmake)

add_subdirectory(command)
add_subdirectory(invoker)
add_subdirectory(test)

add_library(hw7 INTERFACE)

target_sources(hw7
    PRIVATE
    PUBLIC
)

target_link_libraries(hw7
    INTERFACE
        hw7::meta
        libs::command
        libs::invoker
)
