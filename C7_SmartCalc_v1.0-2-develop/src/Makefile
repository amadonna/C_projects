.PHONY: all s21_calc.a test gcov_report check rebuild clean test.o install uninstall dist dvi
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
LC = lcov -c -d .
C_FILES = ./SmartCalc/*.c
O_FILES = *.o
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt -lsubunit
OS=$(shell uname -s)

all : install 
clean : 
	rm -rf *.o *.gcno *.gcda *.info test.out s21_calc.a
	rm -rf ./report
	rm -rf *.dSYM
	rm -fr gcov_test
rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) ./SmartCalc/s21_calc.h
test.o :
	$(CC) $(CFLAGS) -c -lcheck test.c
s21_calc.a :
	$(CC) $(CFLAGS) -c $(C_FILES)
	ar r s21_calc.a $(O_FILES)

test: s21_calc.a s21_smart_calc_test.c
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) s21_smart_calc_test.c s21_calc.a -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) s21_smart_calc_test.c s21_calc.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out	

gcov_report : clean
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test $(C_FILES) s21_smart_calc_test.c $(LIBS) 
else
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test  $(C_FILES) s21_smart_calc_test.c $(LIBS) $(LINUX)
endif
	./gcov_test 
	$(LC) -t "gcov_report" --no-external -o report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

install: uninstall
	make clean
	mkdir build
	cd SmartCalc && qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc/SmartCalc.app build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	mv ./build/SmartCalc.app Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/

dvi:
	open README.md

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./*.c
	clang-format -n ./SmartCalc/*.cpp
	clang-format -n ./SmartCalc/*.c
	clang-format -n ./SmartCalc/*.h
