add_library(in SHARED)

target_sources(in 
    PRIVATE
        in.cpp
    PUBLIC
        in.hpp
)

target_link_libraries(in
    PUBLIC
        cms::modules
)

add_custom_command(TARGET in POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:in> ${LIBS_PATH}
)
