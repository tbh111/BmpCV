cmake_minimum_required(VERSION 3.24)
project(BmpCV)

set(CMAKE_CXX_STANDARD 11)

add_library(BmpCV
        src/bmp.cpp
        src/gui.cpp
        src/img_proc.cpp
        src/transform.cpp
        src/filter.cpp
        src/img_proc_2.cpp)

include_directories(${PROJECT_SOURCE_DIR}/Eigen)
target_include_directories(BmpCV
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
add_subdirectory(test)