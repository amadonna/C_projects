#!/bin/bash

make s21_math.a
gcc -g ./unit_tests.c s21_math.a -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt
CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out
