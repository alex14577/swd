add_library(app STATIC)

target_sources(app
    PRIVATE
        app.cpp
        manager.cpp
    PUBLIC
        app.hpp
        manager.hpp
    INTERFACE
        iface.hpp
    
)

target_link_libraries(app 
    PRIVATE
    PUBLIC
        commands
        exceptions
        command_queue
    INTERFACE
        hw3::meta
)