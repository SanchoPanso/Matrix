#!/bin/sh

g++ -o runner main.cpp matrix.cpp
chmod +x runner && ./runner
