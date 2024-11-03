add_executable(cms_service)

target_sources(cms_service 
    PRIVATE
        main.cpp

)

target_link_libraries(cms_service
    PRIVATE 
        cms::loader
        cms::modules
        cms::worker
    INTERFACE
        cms::meta
    )
