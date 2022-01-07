#!/bin/sh

g++ -o test_runner main.cpp matrix.cpp
chmod +x test_runner && ./test_runner
