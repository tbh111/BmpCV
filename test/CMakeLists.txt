cmake_minimum_required(VERSION 3.24)
project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

message(STATUS "making test program")

add_executable(test test.cpp)

target_include_directories(test
        PRIVATE
        ${PROJECT_SOURCE_DIR}/../include)
target_link_libraries(test
        PRIVATE
        ${PROJECT_SOURCE_DIR}/../cmake-build-debug/libBmpCV.a
        )
