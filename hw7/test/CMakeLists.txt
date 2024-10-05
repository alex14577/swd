add_executable(cmd_test)

target_sources(cmd_test
    PRIVATE
        test.cpp        
    PUBLIC

    INTERFACE
)

target_link_libraries(cmd_test
    PRIVATE
        libs::command
        libs::invoker
        libs::gtest
    INTERFACE
        hw7::meta
)


add_test(cmd_test cmd_test)