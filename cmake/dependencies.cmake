find_package(GTest)

add_library(libs::gtest  ALIAS  GTest::gtest_main)
# add_library(libs::gmock  ALIAS  GTest::gmock_main)

find_package(Boost 1.83 REQUIRED COMPONENTS system filesystem)
if (Boost_FOUND)
    add_library(libs::boost INTERFACE IMPORTED)
    target_include_directories(libs::boost INTERFACE ${Boost_INCLUDE_DIRS})
    target_link_libraries(libs::boost INTERFACE ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost not found!")
endif()