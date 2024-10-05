cmake_minimum_required(VERSION 3.22)
project(swd  LANGUAGES C CXX  VERSION 0.0.1)

option(BUILD_HW1 "Build hw1" OFF)
option(BUILD_HW2 "Build hw2" OFF)
option(BUILD_HW3 "Build hw3" OFF)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror

                    -Wcast-align
                    -Wcast-qual
                    -Wconversion
                    -Wctor-dtor-privacy
                    -Wenum-compare
                    -Wfloat-equal
                    -Wnon-virtual-dtor
                    -Wold-style-cast
                    -Woverloaded-virtual
                    -Wredundant-decls
                    -Wsign-conversion

                    -Wno-sign-promo
                    -Wno-sign-conversion
                    -Wno-unused-function
                    -Wno-unused-parameter
                    -Wno-missing-field-initializers)

add_link_options("-fuse-ld=lld")

link_libraries(debug dl)

enable_testing()
include(cmake/dependencies.cmake)

include(GoogleTest)

if(BUILD_HW1)
    add_subdirectory(hw1)
endif()

if(BUILD_HW2)
    add_subdirectory(hw2)
endif()

if(BUILD_HW3)
    add_subdirectory(hw3)
endif()
if(BUILD_HW4)
    add_subdirectory(hw4)
endif()
if(BUILD_HW5)
    add_subdirectory(hw5)
endif()
if(BUILD_HW7)
    add_subdirectory(hw7)
endif()