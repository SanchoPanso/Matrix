#!/bin/sh

sudo apt-get install libgtest-dev
g++ -o test_runner tests/test_matrix.cpp matrix.cpp
chmod +x test_runner && ./test_runner
