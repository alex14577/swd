add_executable(cms_test test.cpp)

target_link_libraries(cms_test
    PRIVATE 
        libs::gtest
    INTERFACE
    )

gtest_discover_tests(cms_test)