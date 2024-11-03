add_library(out SHARED)

target_sources(out 
    PRIVATE
        out.cpp
    PUBLIC
        out.hpp
)

target_link_libraries(out
    PUBLIC
        cms::modules
)

add_custom_command(TARGET out POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:out> ${LIBS_PATH}
)
