#!/bin/sh

g++ main.cpp -o main.o
g++ matrix.cpp -o matrix.o
g++ -o runner main.o matrix.o

chmod +x runner && ./runner
