
add_executable(equation_solver_test test.cpp)

target_link_libraries(equation_solver_test
    PRIVATE 
        libs::gtest
        equation_solver
    )

gtest_discover_tests(equation_solver_test)