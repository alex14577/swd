cmake_minimum_required(VERSION 3.23)

project(swd  LANGUAGES C CXX  VERSION 0.0.1)

add_compile_options(-Wall -Wextra -Werror)

link_libraries(debug dl)

include(dependencies.cmake)

add_subdirectory(hw1)

