project(tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories("include")
include_directories("src")

add_executable(tests_run main_test.cpp)
target_link_libraries(tests_run gtest gtest_main)