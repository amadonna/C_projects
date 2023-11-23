.PHONY: all s21_string.a test gcov_report check rebuild clean unit_tests.o
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
LC = lcov -c -d .
C_FILES = s21*.c
O_FILES = s21*.o
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt
OS=$(shell uname -s)

all : s21_string.a 
clean : 
	rm -rf *.o *.gcno *.gcda *.info test s21_string.a
	rm -rf ./report
	rm -rf *.dSYM
rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) s21_string.h
unit_tests.o :
	$(CC) $(CFLAGS) -c -lcheck unit_tests.c
s21_string.a :
	$(CC) $(CFLAGS) -c $(C_FILES)
	ar r s21_string.a $(O_FILES)

test: s21_string.a unit_tests.c
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) unit_tests.c s21_string.a -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) unit_tests.c s21_string.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out	

gcov_report : clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test -lcheck $(C_FILES) unit_tests.c
	./gcov_test 
	$(LC) -o report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format
# CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test