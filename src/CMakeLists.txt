cmake_minimum_required(VERSION 3.22)
project(EASy68K)

set(CMAKE_CXX_STANDARD 23)
include_directories("include")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(EASy68K_main
        assemble.cpp
        build.cpp
        codegen.cpp
        directiv.cpp
        EASy68K.cpp
        error.cpp
        eval.cpp
        extern.cpp
        globals.cpp
        instlook.cpp
        insttabl.cpp
        listing.cpp
        LogCtrl.cpp
        macro.cpp
        MainFrame.cpp
        movem.cpp
        object.cpp
        opparse.cpp
        Properties.cpp
        SourceEditCtrl.cpp
        structured.cpp
        symbol.cpp
)
target_link_libraries(EASy68K_main ${wxWidgets_LIBRARIES})

# FOR TESTING
# Get all .cpp files in the current directory
file(GLOB SOURCES *.cpp)
# Add your source files to a library
add_library(EASy68KLib ${SOURCES})
# Include the source directory for headers
target_include_directories(EASy68KLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})