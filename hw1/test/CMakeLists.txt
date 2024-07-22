
add_executable(equation_solver_test test.cpp)

target_link_libraries(equation_solver_test
    PRIVATE 
        equation_solver
    )

add_test(NAME equation_solver_test 
    COMMAND equation_solver_test)