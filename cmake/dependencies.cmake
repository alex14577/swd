find_package(GTest)

add_library(libs::gtest  ALIAS  GTest::gtest_main)
# add_library(libs::gmock  ALIAS  GTest::gmock_main)