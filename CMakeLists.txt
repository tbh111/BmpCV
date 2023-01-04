cmake_minimum_required(VERSION 3.24)
project(BmpCV)

set(CMAKE_CXX_STANDARD 11)

add_library(BmpCV
        src/bmp.cpp
        src/gui.cpp
        src/img_proc.cpp)

include_directories(${PROJECT_SOURCE_DIR}/Eigen)
target_include_directories(BmpCV
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
add_subdirectory(test)