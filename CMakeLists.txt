cmake_minimum_required(VERSION 3.26)
project(EASy68K)

set(CMAKE_CXX_STANDARD 23)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(EASy68K src/MainFrame.cpp)
add_executable(test_run tests/main_test.cpp)
add_subdirectory(tests)
add_subdirectory(src)
target_link_libraries(EASy68K ${wxWidgets_LIBRARIES})
