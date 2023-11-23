
CC = gcc
CFLAG = -Wall -Werror -Wextra



all : s21_grep 

clean :
	rm -rf *.o
	rm -rf s21_grep

rebuild : clean all

s21_grep: 
	$(CC) $(CFLAG) -c s21_grep.c
	$(CC) $(CFLAG) -o s21_grep *.o 