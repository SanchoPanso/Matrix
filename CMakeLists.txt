cmake_minimum_required(VERSION 3.20)
project(matrix)

set(CMAKE_CXX_STANDARD 14)

find_package (GTest REQUIRED)

include_directories (${GTest_INCLUDE_DIRS})
link_directories (${GTest_LIBRARY_DIRS})
add_executable (matrix matrix.cpp tests/test_matrix_gtest.cpp)
target_link_libraries (matrix ${GTest_LIBRARIES})
