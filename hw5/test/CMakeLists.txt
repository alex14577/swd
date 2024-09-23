
add_executable(ioc_test test.cpp)

target_link_libraries(ioc_test
    PRIVATE 
        libs::gtest
        ioc
    INTERFACE
    )

gtest_discover_tests(ioc_test)