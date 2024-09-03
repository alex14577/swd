include(hw5.cmake)

add_subdirectory(ioc)
add_subdirectory(test)

add_library(hw5 INTERFACE)

target_sources(hw5
    PRIVATE
    PUBLIC
)

target_link_libraries(hw5
    INTERFACE
        hw5::meta
)
