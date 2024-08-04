
add_executable(movement_test test.cpp)

target_link_libraries(movement_test
    PRIVATE 
        libs::gtest
        movement
    INTERFACE
        utils
    )

gtest_discover_tests(movement_test)