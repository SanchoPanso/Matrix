#!/bin/sh

g++ tests/test_matrix.cpp matrix.cpp -o test_matrix
chmod +x test_matrix && ./test_matrix

