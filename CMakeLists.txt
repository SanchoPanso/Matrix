cmake_minimum_required(VERSION 3.20)
project(matrix)

set(CMAKE_CXX_STANDARD 14)

add_library(matrixlib matrix.cpp)
add_executable(matrix tests/test_matrix.cpp)
target_link_libraries(matrix matrixlib)
