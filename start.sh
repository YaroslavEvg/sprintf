#!/bin/bash

make
gcc -g ./sprintf.c -o test -lcheck -lcheck -lpthread -lm -lrt -lsubunit
valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test