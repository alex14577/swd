include(hw1.cmake)

add_library(equation_solver STATIC)

target_sources(equation_solver
    PRIVATE
        quadratic.cpp
        details.cpp
)

target_link_libraries(equation_solver
    INTERFACE
        equation_solver::meta
    )

add_subdirectory(test)