add_library(module1 SHARED)

target_sources(module1 
    PRIVATE
        module1.cpp
    PUBLIC
        module1.hpp
)

target_link_libraries(module1
    PUBLIC
        cms::modules
)

add_custom_command(TARGET module1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:module1> ${LIBS_PATH}
)
