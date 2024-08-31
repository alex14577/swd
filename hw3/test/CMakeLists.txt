
add_executable(exceptions_test test.cpp)

target_link_libraries(exceptions_test
    PRIVATE 
        libs::gtest
        app
        logger
    INTERFACE
    )

gtest_discover_tests(exceptions_test)