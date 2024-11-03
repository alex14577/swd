add_library(worker STATIC)
add_library(cms::worker ALIAS worker)

target_sources(worker 
    PRIVATE
        worker.cpp
    
)

target_link_libraries(worker
    PUBLIC
        cms::modules
        cms::commands

)