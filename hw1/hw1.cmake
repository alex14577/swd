add_library(equation_solver_meta  INTERFACE)
add_library(equation_solver::meta ALIAS equation_solver_meta)

target_include_directories(equation_solver_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)