cmake_minimum_required(VERSION 3.23)

project(swd  LANGUAGES C CXX  VERSION 0.0.1)

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

link_libraries(debug dl)

enable_testing()
include(dependencies.cmake)

include(GoogleTest)

add_subdirectory(hw1)