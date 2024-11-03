add_library(commands STATIC)
add_library(cms::commands ALIAS commands)

target_sources(commands
    PRIVATE
        factory.cpp
        PluginExecutor.cpp
        workerStop.cpp
)

target_link_libraries(commands
    PUBLIC
        cms::modules

)