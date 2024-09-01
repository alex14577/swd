
add_executable(commands_test test.cpp)

target_link_libraries(commands_test
    PRIVATE 
        libs::gtest
        macro_command
        utils
        objects
    INTERFACE
        hw4::meta
    )

gtest_discover_tests(commands_test)