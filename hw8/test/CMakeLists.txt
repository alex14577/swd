add_executable(ms_test test.cpp)

target_link_libraries(ms_test
    PRIVATE 
        libs::gtest
        libs::transport
    INTERFACE
    )

gtest_discover_tests(ms_test)