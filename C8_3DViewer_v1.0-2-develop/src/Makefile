.PHONY: all  test gcov_report check rebuild clean test.o install uninstall dist dvi
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
LC = lcov -c -d .
C_FILES = *.c
O_FILES =  *.o
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt 
OS=$(shell uname -s)

all : install 
clean : 
	rm -rf *.o *.gcno *.gcda *.info *.out 
	rm -rf ./report
	rm -rf *.dSYM
rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) backend.h
test.o :
	$(CC) $(CFLAGS) -c -lcheck unit_tests.c


test:  unit_tests.c
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(C_FILES) -o unit_tests.out $(LIBS)
else
	$(CC) $(CFLAGS) $(C_FILES) -o unit_tests.out $(LINUX)
endif
	./unit_tests.out	

gcov_report: clean 
ifeq ($(OS), Darwin)
	$(CC) $(GCOVFLAGS) $(C_FILES) -o report.out $(LIBS)
else
	$(CC) $(GCOVFLAGS) $(C_FILES) -o report.out $(LINUX)
endif
	./report.out
	lcov -t "gcov_report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index.html


install:
	make clean
	rm  -rf build
	mkdir build
	cd 3d_viewer && qmake && make && make clean && rm Makefile && cd ../ && mv 3d_viewer/3dv.app build
	

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_3d_viewer.0/
	mkdir Archive_3d_viewer.0/
	mkdir Archive_3d_viewer.0/src
	mv ./build/3dv.app Archive_3d_viewer.0/src/
	tar cvzf Archive_3d_viewer.tgz Archive_3d_viewer.0/
	rm -rf Archive_3d_viewer.0/

dvi:
	open README_3D_V.md


check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n  3d_viewer/*.h
	clang-format -n  3d_viewer/*.cpp

memcheck:
	make clean  test
	CK_FORK=no leaks -atExit -- ./unit_tests.out

