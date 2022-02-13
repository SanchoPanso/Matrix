#!/bin/sh

g++ -o test_runner tests/test_matrix.cpp matrix.cpp
chmod +x test_runner && ./test_runner
