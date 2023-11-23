CC = gcc
CFLAG = -Wall -Werror -Wextra



all : s21_cat 

clean :
	rm -rf *.o
	rm -rf s21_cat

rebuild : clean all

s21_cat: 
	$(CC) $(CFLAG) -c s21_cat.c
	$(CC) $(CFLAG) -o s21_cat *.o 
