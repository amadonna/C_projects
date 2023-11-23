#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define size 512

char str_1[size] = {'\0'}, str_2[size] = {'\0'};
int int_test1 = 0, int_test2 = 0;

int n = 2100, n1 = 0, n2 = -21;
long int lg = 12345678912345, lg1 = -12345678912345;
short sh = 123, sh1 = -123;

void free_two(char *arr_1, char *arr_2) {
  int len_1 = sizeof(arr_1);
  int len_2 = sizeof(arr_2);

  if (len_1 < len_2) len_1 = len_2;

  for (int i = 0; i < len_1; i++) {
    arr_1[i] = '\0';
    arr_2[i] = '\0';
  }
}

char char_test1 = 'T', char_test2 = 'Z';

START_TEST(StrLen_Test) {
  char mas[] = "Schhol_21\0";
  ck_assert_int_eq(strlen(mas), s21_strlen(mas));

  char mas_2[] = "SCHOOL_21 IN \0 KAZAN!!!";
  ck_assert_int_eq(strlen(mas_2), s21_strlen(mas_2));

  char mas_3[] = "\0";
  ck_assert_int_eq(strlen(mas_3), s21_strlen(mas_3));
}
END_TEST

START_TEST(StrCat_Test) {
  char mas[size] = "";
  char mas_2[size] = "";
  char mas_3[size] = "SCHOOL_21 IN KAZAN";
  ck_assert_pstr_eq(strcat(mas, mas_3), s21_strcat(mas_2, mas_3));

  char mas_4[size] = "IN";
  char mas_5[size] = "IN";
  char mas_6[size] = " KAZAN";
  ck_assert_pstr_eq(strcat(mas_4, mas_6), s21_strcat(mas_5, mas_6));

  char mas_7[size] = "KAZAN";
  char mas_8[size] = "KAZAN";
  char mas_9[size] = " SCHOOL";
  ck_assert_pstr_eq(strcat(mas_7, mas_9), s21_strcat(mas_8, mas_9));
}
END_TEST

START_TEST(StrnCat_Test) {
  s21_size_t count = 2;
  char mas[size] = "";
  char mas_2[size] = "";
  char mas_3[size] = "SCHOOL_21 IN KAZAN";
  ck_assert_pstr_eq(strncat(mas, mas_3, count),
                    s21_strncat(mas_2, mas_3, count));

  count = 3;
  char mas_4[size] = "SCHOOL";
  char mas_5[size] = "SCHOOL";
  char mas_6[size] = "IN KAZAN";
  ck_assert_pstr_eq(strncat(mas_4, mas_6, count),
                    s21_strncat(mas_5, mas_6, count));

  count = 4;
  char mas_7[size] = "SCHOOL";
  char mas_8[size] = "SCHOOL";
  char mas_9[size] = "Programming";
  ck_assert_pstr_eq(strncat(mas_7, mas_9, count),
                    s21_strncat(mas_8, mas_9, count));
}
END_TEST

START_TEST(StrCmp_Test) {
  char mas[] = "SCHOOL";
  char mas_2[] = "SCHOOL";
  int count_1 = s21_strcmp(mas, mas_2);
  int count_2 = strcmp(mas, mas_2);
  ck_assert_int_eq(count_1, count_2);

  char mas_4[] = "SCHOOL PROGRAMMING!";
  char mas_5[] = "SCHOOL OF THE PROGRAMMING";
  count_1 = s21_strcmp(mas_4, mas_5);
  count_2 = strcmp(mas_4, mas_5);
  ck_assert_int_eq(count_1, count_2);

  char mas_6[] = "SCHOOL PROGRAMMING IN KAZAN!";
  char mas_7[] = "SCHOOL";
  count_1 = s21_strcmp(mas_6, mas_7);
  count_2 = strcmp(mas_6, mas_7);
  ck_assert_int_eq(count_1, count_2);
}
END_TEST

START_TEST(StrnCmp_Test) {
  s21_size_t n = 3;
  char mas[] = "SCHOOL!";
  char mas_2[] = "SCHOOL!";
  int count_1 = s21_strncmp(mas, mas_2, n);
  int count_2 = strncmp(mas, mas_2, n);
  ck_assert_int_eq(count_1, count_2);

  n = 4;
  char mas_3[] = "SCHOOL PROGRAMMING!";
  char mas_4[] = "SCHOOL OF THE PROGRAMMING";
  count_1 = s21_strncmp(mas_3, mas_4, n);
  count_2 = strncmp(mas_3, mas_4, n);
  ck_assert_int_eq(count_1, count_2);

  n = 5;
  char mas_5[] = "SCHOOL PROGRAMMING IN KAZAN!";
  char mas_6[] = "SCHOOL ";
  count_1 = s21_strncmp(mas_5, mas_6, n);
  count_2 = strncmp(mas_5, mas_6, n);
  ck_assert_int_eq(count_1, count_2);

  n = 3;
  char mas_7[] = "SCHOOL PROGRAMMING IN KAZAN!";
  char mas_8[] = "NOVOSIB ";
  count_1 = s21_strncmp(mas_7, mas_8, n);
  count_2 = strncmp(mas_7, mas_8, n);
  ck_assert_int_eq(count_1, count_2);
}
END_TEST

START_TEST(MemCmp_Test) {
  s21_size_t n = 3;
  char mas[] = "SCHOOL";
  char mas_2[] = "SCHOOL";
  ck_assert_int_eq(memcmp(mas, mas_2, n), s21_memcmp(mas, mas_2, n));

  n = 4;
  char mas_3[] = "SCHOOL THE PROGRAMMING";
  char mas_4[] = "SCHO OL OF THE PROGRAMMING";
  ck_assert_int_eq(memcmp(mas_3, mas_4, n), s21_memcmp(mas_3, mas_4, n));

  n = 5;
  char mas_5[] = "SCHOOL THE PROGRAMMING";
  char mas_6[] = "SCHOOL";
  ck_assert_int_eq(memcmp(mas_5, mas_6, n), s21_memcmp(mas_5, mas_6, n));
}
END_TEST

START_TEST(MemSet_Test) {
  s21_size_t n = 6;
  int ch = '#';
  char mas[] = "SCHOOL THE PROGRAMMING";
  char mas_2[] = "SCHOOL THE PROGRAMMING";
  ck_assert_pstr_eq(memset(mas, ch, n), s21_memset(mas_2, ch, n));

  n = 4;
  ch = '#';
  char mas_3[] = "PROGRAMMING";
  char mas_4[] = "PROGRAMMING";
  ck_assert_pstr_eq(memset(mas_3, ch, n), s21_memset(mas_4, ch, n));

  n = 5;
  ch = '#';
  char mas_5[] = "KAZAN";
  char mas_6[] = "KAZAN";
  ck_assert_pstr_eq(memset(mas_5, ch, n), s21_memset(mas_6, ch, n));
}
END_TEST

START_TEST(StrCpy_Test) {
  char mas[size] = "";
  char mas_1[size] = "";
  char mas_2[size] = "SCHOOL THE PROGRAMMING";
  ck_assert_pstr_eq(strcpy(mas, mas_2), s21_strcpy(mas_1, mas_2));

  char mas_3[size] = "";
  char mas_4[size] = "";
  char mas_5[size] = "SCHOOL THE \0PROGRAMMING";
  ck_assert_pstr_eq(strcpy(mas_3, mas_5), s21_strcpy(mas_4, mas_5));

  char mas_6[size] = "SCHOOL ";
  char mas_7[size] = "SCHOOL ";
  char mas_8[size] = "THE PROGRAMMING";
  ck_assert_pstr_eq(strcpy(mas_6, mas_8), s21_strcpy(mas_7, mas_8));
}
END_TEST

START_TEST(StrnCpy_Test) {
  s21_size_t n = 3;
  char mas[size] = "SCHOOL ";
  char mas_1[size] = "SCHOOL ";
  char mas_2[size] = "THE PROGRAMMING";
  ck_assert_pstr_eq(strncpy(mas, mas_2, n), s21_strncpy(mas_1, mas_2, n));

  n = 5;
  char mas_3[size] = "KAZAN";
  char mas_4[size] = "KAZAN";
  char mas_5[size] = "";
  ck_assert_pstr_eq(strncpy(mas_3, mas_5, n), s21_strncpy(mas_4, mas_5, n));

  n = 3;
  char mas_6[size] = "77";
  char mas_7[size] = "77";
  char mas_8[size] = "KAZAN\0SCHOOL";
  ck_assert_pstr_eq(strncpy(mas_6, mas_8, n), s21_strncpy(mas_7, mas_8, n));

  n = 0;
  char mas_9[] = "";
  char mas_10[] = "";
  char mas_11[] = "";
  ck_assert_str_eq(strncpy(mas_10, mas_11, n), s21_strncpy(mas_9, mas_11, n));
}
END_TEST

START_TEST(MemCpy_Test) {
  s21_size_t n = 3;
  char mas[] = "THE";
  char mas_1[] = "THE";
  char mas_2[] = "    PROGRAMMING";
  ck_assert_pstr_eq(memcpy(mas, mas_2, n), s21_memcpy(mas_1, mas_2, n));

  n = 5;
  char mas_3[] = "KAZAN";
  char mas_4[] = "KAZAN";
  char mas_5[size] = "";
  ck_assert_pstr_eq(memcpy(mas_3, mas_5, n), s21_memcpy(mas_4, mas_5, n));

  n = 4;
  char mas_6[] = "777 ";
  char mas_7[] = "777 ";
  char mas_8[] = "KAZAN";
  ck_assert_pstr_eq(memcpy(mas_6, mas_8, n), s21_memcpy(mas_7, mas_8, n));
}
END_TEST

START_TEST(MemMove_Test) {
  s21_size_t n = 3;
  char mas[] = "SCHHOL PROGRAMMING IN KAZAN";
  char mas_2[] = "SCHHOL PROGRAMMING IN KAZAN";
  ck_assert_pstr_eq(memmove(mas, mas + 5, n), s21_memmove(mas_2, mas + 5, n));

  n = 7;
  char mas_3[] = "SCHHOL PROGRAMMING";
  char mas_4[] = "SCHHOL PROGRAMMING";
  ck_assert_pstr_eq(memmove(mas_3, mas_3, n), s21_memmove(mas_4, mas_3, n));

  n = 7;
  char mas_5[] = "SCHHOL ";
  char mas_6[] = "SCHHOL ";
  ck_assert_pstr_eq(memmove(mas_5, mas_5, n), s21_memmove(mas_6, mas_6, n));
}
END_TEST

START_TEST(MemChr_Test) {
  char mas[] = "SCHOOL P\0ROGRaMMING\0";
  ck_assert_pstr_eq(memchr(mas, 'a', 5), s21_memchr(mas, 'a', 5));

  char mas_2[] = "WORLD CUP FIFA";
  ck_assert_pstr_eq(memchr(mas_2, 'R', 6), s21_memchr(mas_2, 'R', 6));

  char mas_3[] = "QwERtY";
  ck_assert_pstr_eq(memchr(mas_3, 'w', 5), s21_memchr(mas_3, 'w', 5));
}
END_TEST

START_TEST(StrError_Test) {
  int err_num = 7;
  ck_assert_pstr_eq(strerror(err_num), s21_strerror(err_num));

  int err_num2 = 1;
  ck_assert_pstr_eq(strerror(err_num2), s21_strerror(err_num2));

  int err_num3 = 404;
  ck_assert_pstr_eq(strerror(err_num3), s21_strerror(err_num3));

  int err_num4 = 0;
  ck_assert_pstr_eq(strerror(err_num4), s21_strerror(err_num4));

  int err_num5 = -1;
  ck_assert_pstr_eq(strerror(err_num5), s21_strerror(err_num5));
}
END_TEST

START_TEST(StrChr_Test) {
  char mas[] = "Hello World";
  ck_assert_pstr_eq(strchr(mas, ' '), s21_strchr(mas, ' '));

  char mas_2[] = "School_programming\0 in Kazan";
  ck_assert_pstr_eq(strchr(mas_2, 'm'), s21_strchr(mas_2, 'm'));

  char mas_3[] = "School programming in Kazan";
  ck_assert_pstr_eq(strchr(mas_3, 'i'), s21_strchr(mas_3, 'i'));
}
END_TEST

START_TEST(StrrChr_Test) {
  char mas[] = "012356789";
  ck_assert_pstr_eq(strrchr(mas, '8'), s21_strrchr(mas, '8'));

  char mas_2[] = "school programm@ing in kazan";
  ck_assert_pstr_eq(strrchr(mas_2, '@'), s21_strrchr(mas_2, '@'));

  char mas_3[] = "school programm@ing in kazan";
  ck_assert_pstr_eq(strrchr(mas_3, 'g'), s21_strrchr(mas_3, 'g'));

  char mas_4[] = "school. programming in kazan";
  ck_assert_pstr_eq(strrchr(mas_4, '.'), s21_strrchr(mas_4, '.'));

  char mas_5[] = "";
  ck_assert_pstr_eq(strrchr(mas_5, 'z'), s21_strrchr(mas_5, 'z'));
}
END_TEST

START_TEST(StrcSpn_Test) {
  char mas[] = "work in this school";
  ck_assert_int_eq(strcspn(mas, "is"), s21_strcspn(mas, "is"));

  char mas_2[] = "NUMBER: 4-8-15-16-23-42";
  ck_assert_int_eq(strcspn(mas_2, "1234567890"),
                   s21_strcspn(mas_2, "1234567890"));

  char mas_3[] = "qwertsxzac\0";
  ck_assert_int_eq(strcspn(mas_3, "zx"), s21_strcspn(mas_3, "zx"));
}
END_TEST

START_TEST(StrSpn_Test) {
  char mas[] = "12-years";
  ck_assert_int_eq(strspn(mas, "1234567890"), s21_strspn(mas, "1234567890"));

  char mas_2[] = "this is a test";
  ck_assert_int_eq(strspn(mas_2, "shit "), s21_strspn(mas_2, "shit "));

  char mas_3[] = "qwertyhgfdsa";
  ck_assert_int_eq(strspn(mas_3, "01234"), s21_strspn(mas_3, "01234"));
}
END_TEST

START_TEST(StrPbrk_Test) {
  char mas[] = "this_is_a_";
  ck_assert_pstr_eq(strpbrk(mas, "369"), s21_strpbrk(mas, "369"));

  char mas_2[] = "school programm@ing in kazan";
  ck_assert_pstr_eq(strpbrk(mas_2, "fzx"), s21_strpbrk(mas_2, "fzx"));

  char mas_3[] = "qrstwsas\0";
  ck_assert_pstr_eq(strpbrk(mas_3, "saq"), s21_strpbrk(mas_3, "saq"));
}
END_TEST

START_TEST(StrStr_Test) {
  char mas[] = "";
  ck_assert_pstr_eq(strstr(mas, ""), s21_strstr(mas, ""));

  char mas_2[] = "school progr\0ing in kazan";
  ck_assert_pstr_eq(strstr(mas_2, "progr"), s21_strstr(mas_2, "progr"));

  char mas_3[] = "qrstwsas\0";
  ck_assert_pstr_eq(strstr(mas_3, "sas"), s21_strstr(mas_3, "sas"));
}
END_TEST

START_TEST(StrTok_Test) {
  char mas[] = "/testing/with/original/string.h/";
  char mas_1[] = "/testing/with/original/string.h/";
  char del_2[3] = "/";
  char *nstr_1, *nstr_2;
  nstr_1 = strtok(mas, del_2);
  nstr_2 = s21_strtok(mas_1, del_2);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del_2);
    nstr_2 = s21_strtok(s21_NULL, del_2);
  }

  char mas_4[] = ". . testing with original string.h";
  char mas_5[] = ". . testing with original string.h";
  char del_6[3] = ". ";
  nstr_1 = strtok(mas_4, del_6);
  nstr_2 = s21_strtok(mas_5, del_6);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del_6);
    nstr_2 = s21_strtok(s21_NULL, del_6);
  }

  char mas_7[] = "testing with original string.h";
  char mas_8[] = "testing with original string.h";
  char del_9[3] = ". ";
  nstr_1 = strtok(mas_7, del_9);
  nstr_2 = s21_strtok(mas_8, del_9);
  while (nstr_1 != s21_NULL) {
    ck_assert_pstr_eq(nstr_1, nstr_2);
    nstr_1 = strtok(s21_NULL, del_9);
    nstr_2 = s21_strtok(s21_NULL, del_9);
  }
}
END_TEST

START_TEST(To_Up_Test) {
  char mas[] = "School_21 in kazan";
  char *mas_2 = s21_to_upper(mas);
  ck_assert_pstr_eq(mas_2, "SCHOOL_21 IN KAZAN");
  free(mas_2);

  char mas_3[] = "1+1*1";
  char *mas_4 = s21_to_upper(mas_3);
  ck_assert_str_eq(mas_4, "1+1*1");
  free(mas_4);
}
END_TEST

START_TEST(To_Low_Test) {
  char mas[] = "sCHOOL_21 IN KAZAN!";
  char *mas_2 = s21_to_lower(mas);
  ck_assert_pstr_eq(mas_2, "school_21 in kazan!");

  char mas_3[] = "1+1*1";
  char *mas_4 = s21_to_lower(mas_3);
  ck_assert_str_eq(mas_4, "1+1*1");
}
END_TEST

START_TEST(Insert_Test) {
  char mas[] = "dom";
  char *mas_2;
  mas_2 = s21_insert(mas, "ran", 0);
  ck_assert_pstr_eq(mas_2, "random");

  char mas_3[] = "random";
  mas_2 = s21_insert(mas_3, "maz", 8);
  ck_assert_pstr_eq(mas_2, s21_NULL);

  char *mas_4 = s21_NULL;
  mas_2 = s21_insert(mas_4, "maz", 2);
  ck_assert_pstr_eq(mas_2, s21_NULL);

  char *mas_5 = s21_NULL;
  mas_2 = s21_insert(mas_4, mas_5, 0);
  ck_assert_pstr_eq(mas_2, s21_NULL);
}
END_TEST

START_TEST(Trim_Test) {
  char mas[] = "     &#@\n\n\t Hello, World! *&#@ \n\t   ";
  char trim_chars[] = " &#@\n\t";
  char *psrc = s21_trim(mas, trim_chars);
  ck_assert_pstr_eq(psrc, "Hello, World! *");

  char mas_2[] = "    \n\tHello, World! *&#@ \n\t   ";
  char trim_chars_2[] = "";
  char *psrc_2 = s21_trim(mas_2, trim_chars_2);
  ck_assert_pstr_eq(psrc_2, "Hello, World! *&#@");

  char mas_3[] = "*1234";
  char trim_chars_3[] = "*1234";
  char *psrc_3 = s21_trim(mas_3, trim_chars_3);
  ck_assert_pstr_eq(psrc_3, "\0");
}
END_TEST

START_TEST(Atoi_Test) {
  char mas[] = "  +123123123";
  ck_assert_int_eq(atoi(mas), s21_atoi(mas));

  char mas_2[] = "-123123123";
  ck_assert_int_eq(atoi(mas_2), s21_atoi(mas_2));
}
END_TEST

START_TEST(Sprintf_Test_s) {
  s21_sprintf(str_1, "%s", "Hello");
  sprintf(str_2, "%s", "Hello");
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%.1s", "Hello");
  sprintf(str_2, "%.1s", "Hello");
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%7s", "Hello");
  sprintf(str_2, "%7s", "Hello");
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10s", "Hello");
  sprintf(str_2, "%-10s", "Hello");
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "qwerty %s qwe", "qwerty");
  sprintf(str_2, "qwerty %s qwe", "qwerty");
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%s", "");
  int_test2 = sprintf(str_2, "%s", "");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%23s", "aboba");
  int_test2 = sprintf(str_2, "%23s", "aboba");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-15s", "helloworld");
  int_test2 = sprintf(str_2, "%-15s", "helloworld");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%10.s", "ABOBA");
  int_test2 = sprintf(str_2, "%10.s", "ABOBA");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%15.2s", "ABOBBAAA");
  int_test2 = sprintf(str_2, "%15.2s", "ABOBBAAA");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%16.*s", 10, "QWERTY");
  int_test2 = sprintf(str_2, "%16.*s", 10, "QWERTY");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.*s", 15, 4, "AAAAABOOOOOBAAA");
  int_test2 = sprintf(str_2, "%*.*s", 15, 4, "AAAAABOOOOOBAAA");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*s", 10, "ABOBAAAAA");
  int_test2 = sprintf(str_2, "%*s", 10, "ABOBAAAAA");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%s %10s", "hello", "hello");
  int_test2 = sprintf(str_2, "%s %10s", "hello", "hello");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%.s %.3s %.10s", "hello", "hello", "hello");
  int_test2 = sprintf(str_2, "%.s %.3s %.10s", "hello", "hello", "hello");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10s %-3s", "hello", "hello");
  int_test2 = sprintf(str_2, "%-10s %-3s", "hello", "hello");
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_c) {
  s21_sprintf(str_1, "%10c", 'a');
  sprintf(str_2, "%10c", 'a');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10c", 'e');
  sprintf(str_2, "%-10c", 'e');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%c hello %c", '\0', '\0');
  sprintf(str_2, "%c hello %c", '\0', '\0');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%25c", 'f');
  sprintf(str_2, "%25c", 'f');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-30c", 'R');
  sprintf(str_2, "%-30c", 'R');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%25c", 'Q');
  sprintf(str_2, "%25c", 'Q');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%*c", 10, 'P');
  sprintf(str_2, "%*c", 10, 'P');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%2c", 'L');
  sprintf(str_2, "%2c", 'L');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%*c", 20, 'x');
  sprintf(str_2, "%*c", 20, 'x');
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%lc", char_test1);
  sprintf(str_2, "%lc", char_test1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%c", CHAR_MAX);
  sprintf(str_2, "%c", CHAR_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%c", CHAR_MIN);
  sprintf(str_2, "%c", CHAR_MIN);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%c", UCHAR_MAX);
  sprintf(str_2, "%c", UCHAR_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
  sprintf(str_2, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-50lc", char_test2);
  sprintf(str_2, "%-50lc", char_test2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e', 'f',
              'R', 'Q', 10, 'P', 'L', 20, 'x', char_test1, char_test2);
  sprintf(str_2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e', 'f', 'R',
          'Q', 10, 'P', 'L', 20, 'x', char_test1, char_test2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(
      str_1, "%10c%-10cdsad%25c%-30c  %25c%*c%2c%*csadasaaaWWW%lc%-50lc", 'a',
      'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', char_test1, char_test2);
  sprintf(str_2, "%10c%-10cdsad%25c%-30c  %25c%*c%2c%*csadasaaaWWW%lc%-50lc",
          'a', 'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', char_test1,
          char_test2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%c", '!');
  sprintf(str_2, "%c", '!');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%10c", 'a');
  sprintf(str_2, "%10c", 'a');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10c", 'b');
  sprintf(str_2, "%-10c", 'b');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%c %10c %-10c", '!', 'a', 'b');
  sprintf(str_2, "%c %10c %-10c", '!', 'a', 'b');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%1c %c", 'H', 'z');
  sprintf(str_2, "%1c %c", 'H', 'z');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%10c %2c", 'H', 'z');
  sprintf(str_2, "%10c %2c", 'H', 'z');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-1c %-c", 'H', 'z');
  sprintf(str_2, "%-1c %-c", 'H', 'z');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %3c abc", '*');
  sprintf(str_2, "abc %3c abc", '*');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %-3c abc", '*');
  sprintf(str_2, "abc %-3c abc", '*');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "qwerty %c %-5c %15c", '$', '/', '!');
  sprintf(str_2, "qwerty %c %-5c %15c", '$', '/', '!');
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_f) {
  s21_sprintf(str_1, "abc %+.4f abc", 166.087);
  sprintf(str_2, "abc %+.4f abc", 166.087);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %-12.3f abc", 166.87);
  sprintf(str_2, "abc %-12.3f abc", 166.87);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %f abc", -166.87);
  sprintf(str_2, "abc %f abc", -166.87);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%f", 100000.4);
  sprintf(str_2, "%f", 100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%0f", 100000.4);
  sprintf(str_2, "%0f", 100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%f", -100000.4);
  sprintf(str_2, "%f", -100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%+f %+f", -100000.4, 1000.231);
  sprintf(str_2, "%+f %+f", -100000.4, 1000.231);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-20f", 100000.4);
  sprintf(str_2, "%-20f", 100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %Lf", (long double)58787.878958);
  sprintf(str_2, "abc %Lf", (long double)58787.878958);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %.lf", 58787.878958);
  sprintf(str_2, "abc %.lf", 58787.878958);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %.10f", 587.00089);
  sprintf(str_2, "abc %.10f", 587.00089);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-+20f", 100000.4);
  sprintf(str_2, "%-+20f", 100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-20f", -100000.4);
  sprintf(str_2, "%-20f", -100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%+20f", 100000.4);
  sprintf(str_2, "%+20f", 100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%+20f", -100000.4);
  sprintf(str_2, "%+20f", -100000.4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  float key = 10000;
  s21_sprintf(str_1, "%+20f", key);
  sprintf(str_2, "%+20f", key);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+-10.5f", 2546.4324);
  int_test2 = sprintf(str_2, "%+-10.5f", 2546.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+10.2f", 3452.4325);
  int_test2 = sprintf(str_2, "%+10.2f", 3452.4325);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%15.16f", 5678.43256);
  int_test2 = sprintf(str_2, "%15.16f", 5678.43256);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+*.10f", 25, 456789.243242);
  int_test2 = sprintf(str_2, "%+*.10f", 25, 456789.243242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.16f", 10, 3456789123.43245);
  int_test2 = sprintf(str_2, "%*.16f", 10, 3456789123.43245);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10.*f", 2, 12345.6788);
  int_test2 = sprintf(str_2, "%-10.*f", 2, 12345.6788);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%25.*f", 1, 34.4325432);
  int_test2 = sprintf(str_2, "%25.*f", 1, 34.4325432);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%25.f", 4325678.43242);
  int_test2 = sprintf(str_2, "%25.f", 4325678.43242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#+10.f", 34567.2345432);
  int_test2 = sprintf(str_2, "%#+10.f", 34567.2345432);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.*f", 10, 2, 34567.43244);
  int_test2 = sprintf(str_2, "%*.*f", 10, 2, 34567.43244);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)UINT_MAX);
  int_test2 = sprintf(str_2, "%f", (double)UINT_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)INT_MAX);
  int_test2 = sprintf(str_2, "%f", (double)INT_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)INT_MIN);
  int_test2 = sprintf(str_2, "%f", (double)INT_MIN);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)SHRT_MAX);
  int_test2 = sprintf(str_2, "%f", (double)SHRT_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)SHRT_MIN);
  int_test2 = sprintf(str_2, "%f", (double)SHRT_MIN);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)LONG_MIN);
  int_test2 = sprintf(str_2, "%f", (double)LONG_MIN);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)USHRT_MAX);
  int_test2 = sprintf(str_2, "%f", (double)USHRT_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%f", (double)LONG_MAX);
  int_test2 = sprintf(str_2, "%f", (double)LONG_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1,
      "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  int_test2 = sprintf(
      str_2,
      "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1,
      "%+-10.5f  "
      "%+10.2f%15.16dasdf%+*.10f%*.16f%-10.*fdsad%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 567843256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  int_test2 = sprintf(
      str_2,
      "%+-10.5f  "
      "%+10.2f%15.16dasdf%+*.10f%*.16f%-10.*fdsad%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 567843256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  char str1[size];
  char str2[size];
  char *format = "%Lf";
  long double val = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(Sprintf_Test_d) {
  s21_sprintf(str_1, "%-10d", 21);
  sprintf(str_2, "%-10d", 21);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%010d %010d", n2, n);
  sprintf(str_2, "%010d %010d", n2, n);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%*d %2d", -5, n2, n);
  sprintf(str_2, "%*d %2d", -5, n2, n);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %d abc", -166);
  sprintf(str_2, "abc %d abc", -166);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%d%%\n", 4);
  sprintf(str_2, "%d%%\n", 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%.10d%%\n", 4);
  sprintf(str_2, "%.10d%%\n", 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %010d", 50);
  sprintf(str_2, "abc %010d", 50);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%0d%%\n", -4);
  sprintf(str_2, "%0d%%\n", -4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-+10d%%\n", 4);
  sprintf(str_2, "%-+10d%%\n", 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10d%%\n", -4);
  sprintf(str_2, "%-10d%%\n", -4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%+10d%%\n", 4);
  sprintf(str_2, "%+10d%%\n", 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%.2d", 4);
  sprintf(str_2, "%.2d", 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%+10d%%\n", -4);
  sprintf(str_2, "%+10d%%\n", -4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%.*d %3.10d %.d", 10, n, n2, 42);
  int_test2 = sprintf(str_2, "%.*d %3.10d %.d", 10, n, n2, 42);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-+.5d %-+10.5d", 21, 10);
  int_test2 = sprintf(str_2, "%-+.5d %-+10.5d", 21, 10);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+010d %+-10d", n2, n);
  int_test2 = sprintf(str_2, "%+010d %+-10d", n2, n);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "% -10d %-10d %-10d", 21, 55, -55);
  int_test2 = sprintf(str_2, "% -10d %-10d %-10d", 21, 55, -55);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%.10d %.10d", n, n2);
  int_test2 = sprintf(str_2, "%.10d %.10d", n, n2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 =
      s21_sprintf(str_1, "%2.2d %.d % d %.0d", -21, char_test1, 21, -42);
  int_test2 = sprintf(str_2, "%2.2d %.d % d %.0d", -21, char_test1, 21, -42);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%hd %hd", sh, sh1);
  int_test2 = sprintf(str_2, "%hd %hd", sh, sh1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%ld %ld", lg, lg1);
  int_test2 = sprintf(str_2, "%ld %ld", lg, lg1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%10ld", lg1);
  int_test2 = sprintf(str_2, "%10ld", lg1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%+10.5d%%\n", -4);
  sprintf(str_2, "%+10.5d%%\n", -4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  long int var_long = 100;
  s21_sprintf(str_1, "%ld%%\n", var_long);
  sprintf(str_2, "%ld%%\n", var_long);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  short var_short = 123;
  s21_sprintf(str_1, "%hd%%\n", var_short);
  sprintf(str_2, "%hd%%\n", var_short);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %ld", 58787878958);
  sprintf(str_2, "abc %ld", 58787878958);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %d", 87878958);
  sprintf(str_2, "abc %d", 87878958);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %hd", 87878958);
  sprintf(str_2, "abc %hd", (short)87878958);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %*d", 5, 4);
  sprintf(str_2, "abc %*d", 5, 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%d%d", INT_MIN, INT_MAX);
  int_test2 = sprintf(str_2, "%d%d", INT_MIN, INT_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%d%d", SHRT_MAX, SHRT_MIN);
  int_test2 = sprintf(str_2, "%d%d", SHRT_MAX, SHRT_MIN);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%d %d", SHRT_MIN, USHRT_MAX);
  int_test2 = sprintf(str_2, "%d %d", SHRT_MIN, USHRT_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%ld", LONG_MAX);
  int_test2 = sprintf(str_2, "%ld", LONG_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%ld", LONG_MIN);
  int_test2 = sprintf(str_2, "%ld", LONG_MIN);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%ld", -9223372036854775807 - 1);
  int_test2 = sprintf(str_2, "%ld", -9223372036854775807 - 1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-25.10d", 253);
  int_test2 = sprintf(str_2, "%-25.10d", 253);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-30.2d", 335);
  int_test2 = sprintf(str_2, "%-30.2d", 335);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%10.12d", 1234);
  int_test2 = sprintf(str_2, "%10.12d", 1234);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%11d", 34);
  int_test2 = sprintf(str_2, "%11d", 34);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*d", 10, 25);
  int_test2 = sprintf(str_2, "%*d", 10, 25);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.*d", 5, 15, 345);
  int_test2 = sprintf(str_2, "%*.*d", 5, 15, 345);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+-25.*d", 5, 15);
  int_test2 = sprintf(str_2, "%+-25.*d", 5, 15);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+-25.*d", 45, 5);
  int_test2 = sprintf(str_2, "%+-25.*d", 45, 5);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+10.2ld", 456789l);
  int_test2 = sprintf(str_2, "%+10.2ld", 456789l);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-11.*hd", 5, sh);
  int_test2 = sprintf(str_2, "%-11.*hd", 5, sh);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, sh);
  int_test2 = sprintf(
      str_2, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, sh);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_u) {
  s21_sprintf(str_1, "abc %u abc", 166);
  sprintf(str_2, "abc %u abc", 166);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%2.5u%%\n", 4);
  sprintf(str_2, "%2.5u%%\n", 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%2.5u%%\n", -4);
  sprintf(str_2, "%2.5u%%\n", -4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%10.5u%%\n", 4);
  sprintf(str_2, "%10.5u%%\n", 4);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10u%%\n", 421);
  sprintf(str_2, "%-10u%%\n", 421);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  short unsigned key_h = 421;
  s21_sprintf(str_1, "%-10hu%%\n", key_h);
  sprintf(str_2, "%-10hu%%\n", key_h);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  long unsigned key_l = 421;
  s21_sprintf(str_1, "%-10lu%%\n", key_l);
  sprintf(str_2, "%-10lu%%\n", key_l);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %hu", 17);
  sprintf(str_2, "abc %hu", (unsigned short)17);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %lu", 17123121);
  sprintf(str_2, "abc %lu", (long unsigned int)17123121);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%u", 4321u);
  int_test2 = sprintf(str_2, "%u", 4321u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%15u", 34567u);
  int_test2 = sprintf(str_2, "%15u", 34567u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-20u", 2342u);
  int_test2 = sprintf(str_2, "%-20u", 2342u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%010u", 12346u);
  int_test2 = sprintf(str_2, "%010u", 12346u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-15.10u", 234542u);
  int_test2 = sprintf(str_2, "%-15.10u", 234542u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%20.*u", 10, 234523u);
  int_test2 = sprintf(str_2, "%20.*u", 10, 234523u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.*u", 10, 5, 2345u);
  int_test2 = sprintf(str_2, "%*.*u", 10, 5, 2345u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.10u", 20, 2432u);
  int_test2 = sprintf(str_2, "%*.10u", 20, 2432u);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-20.12lu", lg);
  int_test2 = sprintf(str_2, "%-20.12lu", lg);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%19hu", sh);
  int_test2 = sprintf(str_2, "%19hu", sh);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%u", UINT_MAX);
  int_test2 = sprintf(str_2, "%u", UINT_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%lu", ULONG_MAX);
  int_test2 = sprintf(str_2, "%lu", ULONG_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%u %lu", UINT_MAX, ULONG_MAX);
  int_test2 = sprintf(str_2, "%u %lu", UINT_MAX, ULONG_MAX);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu", 4321u,
      34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, lg,
      sh);
  int_test2 =
      sprintf(str_2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
              4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u,
              20, 2432u, lg, sh);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1,
                          "%u%15uhhhh%-20u%010u  fsd  %-15.10u%20.*u sdss "
                          "%*.*u%*.10u%-20.12lu%19hu",
                          4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u,
                          10, 5, 2345u, 20, 2432u, lg, sh);
  int_test2 = sprintf(str_2,
                      "%u%15uhhhh%-20u%010u  fsd  %-15.10u%20.*u sdss "
                      "%*.*u%*.10u%-20.12lu%19hu",
                      4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5,
                      2345u, 20, 2432u, lg, sh);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_x) {
  s21_sprintf(str_1, "%x %x", n, n1);
  sprintf(str_2, "%x %x", n, n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%10x %-10x", 21, n);
  sprintf(str_2, "%10x %-10x", 21, n);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#4.x", 25);
  sprintf(str_2, "%#4.x", 25);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%.10x %.0x", n, 0);
  sprintf(str_2, "%.10x %.0x", n, 0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#5.10x", 123);
  sprintf(str_2, "%#5.10x", 123);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21,
              n, 0, 123);
  sprintf(str_2, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n,
          0, 123);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#x %#x", n, n2);
  sprintf(str_2, "%#x %#x", n, n2);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#10x %#10x", 21, 0);
  sprintf(str_2, "%#10x %#10x", 21, 0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-#10x %0#10x %0#10x", 42, 21, 0);
  sprintf(str_2, "%-#10x %0#10x %0#10x", 42, 21, 0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10.5x %lx %lx", -65, lg, lg1);
  sprintf(str_2, "%-10.5x %lx %lx", -65, lg, lg1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
              n, n2, 21, 0, 42, 21, 0, -65, lg, lg1);
  sprintf(str_2, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx", n,
          n2, 21, 0, 42, 21, 0, -65, lg, lg1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %x", 4784);
  sprintf(str_2, "abc %x", 4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %#x", 4784);
  sprintf(str_2, "abc %#x", 4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %x", 0);
  sprintf(str_2, "abc %x", 0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_o) {
  s21_sprintf(str_1, "abc %o", 4784);
  sprintf(str_2, "abc %o", 4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %#o", 4784);
  sprintf(str_2, "abc %#o", 4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %o", 0);
  sprintf(str_2, "abc %o", 0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %*o", -5, 0);
  sprintf(str_2, "abc %*o", -5, 0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-25.10o", 12345);
  int_test2 = sprintf(str_2, "%-25.10o", 12345);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10o", 6532);
  int_test2 = sprintf(str_2, "%-10o", 6532);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#-30.2o", 43522);
  int_test2 = sprintf(str_2, "%#-30.2o", 43522);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#*.10o", 10, 64342);
  int_test2 = sprintf(str_2, "%#*.10o", 10, 64342);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#*.*o", 15, 2, 343);
  int_test2 = sprintf(str_2, "%#*.*o", 15, 2, 343);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%25.*o", 6, 678);
  int_test2 = sprintf(str_2, "%25.*o", 6, 678);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#.10ho", sh);
  int_test2 = sprintf(str_2, "%#.10ho", sh);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*lo", 10, lg);
  int_test2 = sprintf(str_2, "%*lo", 10, lg);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10o", 21);
  int_test2 = sprintf(str_2, "%-10o", 21);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%lo", lg);
  int_test2 = sprintf(str_2, "%lo", lg);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%lo %o %o", lg1, n, 0);
  int_test2 = sprintf(str_2, "%lo %o %o", lg1, n, 0);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%o %10o", n2, 0);
  int_test2 = sprintf(str_2, "%o %10o", n2, 0);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#10o %0#10o", 21, 42);
  int_test2 = sprintf(str_2, "%#10o %0#10o", 21, 42);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#o", n);
  int_test2 = sprintf(str_2, "%#o", n);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#o %#10o", n2, 0);
  int_test2 = sprintf(str_2, "%#o %#10o", n2, 0);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%0#10o %.10o", 0, n);
  int_test2 = sprintf(str_2, "%0#10o %.10o", 0, n);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%.0o %#5.10o", 0, 123);
  int_test2 = sprintf(str_2, "%.0o %#5.10o", 0, 123);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo", 12345, 6532,
      43522, 10, 64342, 15, 2, 343, 6, 678, sh, 10, lg);
  int_test2 =
      sprintf(str_2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
              12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, sh, 10, lg);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1,
      "%-25.10o  %-10o  fdsf %#-30.2oGGGD#%#*.10o%#*.*o%25.*o%#.10ho%*lo",
      12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, sh, 10, lg);
  int_test2 = sprintf(
      str_2,
      "%-25.10o  %-10o  fdsf %#-30.2oGGGD#%#*.10o%#*.*o%25.*o%#.10ho%*lo",
      12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, sh, 10, lg);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_e) {
  int_test1 = s21_sprintf(str_1, "%+-20e", 2543.43254);
  int_test2 = sprintf(str_2, "%+-20e", 2543.43254);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%010.*e", 10, 1012.34567);
  int_test2 = sprintf(str_2, "%010.*e", 10, 1012.34567);
  ck_assert_int_eq(int_test1, int_test2);
  ck_assert_str_eq(str_1, str_2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#02.e", 25.432523432);
  int_test2 = sprintf(str_2, "%#02.e", 25.432523432);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %e", 0.4784);
  sprintf(str_2, "abc %e", 0.4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %e", 7.8);
  sprintf(str_2, "abc %e", 7.8);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %e", 17.8);
  sprintf(str_2, "abc %e", 17.8);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %Le", (long double)17.8);
  sprintf(str_2, "abc %Le", (long double)17.8);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+-20e", 2543.43254);
  int_test2 = sprintf(str_2, "%+-20e", 2543.43254);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-*.16e", 10, 1012.34567);
  int_test2 = sprintf(str_2, "%-*.16e", 10, 1012.34567);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%010.*e", 15, -0.00123);
  int_test2 = sprintf(str_2, "%010.*e", 15, -0.00123);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#025.10e", 45678.342532);
  int_test2 = sprintf(str_2, "%#025.10e", 45678.342532);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.*e", 10, 15, 11111.22);
  int_test2 = sprintf(str_2, "%*.*e", 10, 15, 11111.22);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.15e", 16, -3245.3425342);
  int_test2 = sprintf(str_2, "%*.15e", 16, -3245.3425342);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#010.*e", 16, -0.00123);
  int_test2 = sprintf(str_2, "%#010.*e", 16, -0.00123);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%25.16e", 235423424.43252);
  int_test2 = sprintf(str_2, "%25.16e", 235423424.43252);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
      2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15, 11111.22,
      16, -3245.3425342, 16, -0.00123, 235423424.43252);
  int_test2 =
      sprintf(str_2, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
              2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
              11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(
      str_1,
      "%+-20e  fds%010.*e%-*.16ebbbbb%#025.10e v %*.*e%*.15e%#010.*e%25.16e",
      2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15, 11111.22,
      16, -3245.3425342, 16, -0.00123, 235423424.43252);
  int_test2 = sprintf(
      str_2,
      "%+-20e  fds%010.*e%-*.16ebbbbb%#025.10e v %*.*e%*.15e%#010.*e%25.16e",
      2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15, 11111.22,
      16, -3245.3425342, 16, -0.00123, 235423424.43252);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_i) {
  s21_sprintf(str_1, "abc %-20i abc", 5);
  sprintf(str_2, "abc %-20i abc", 5);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %020i abc", 5);
  sprintf(str_2, "abc %020i abc", 5);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %.20i abc", 1234567890);
  sprintf(str_2, "abc %.20i abc", 1234567890);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %*i abc", 20, 1234567890);
  sprintf(str_2, "abc %*i abc", 20, 1234567890);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %.*i abc", 20, 1234567890);
  sprintf(str_2, "abc %.*i abc", 20, 1234567890);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc % 5i abc", 5);
  sprintf(str_2, "abc % 5i abc", 5);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %3i abc", 5);
  sprintf(str_2, "abc %3i abc", 5);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "abc %+i abc", 5);
  int_test2 = sprintf(str_2, "abc %+i abc", 5);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "abc %-.i abc", n);
  int_test2 = sprintf(str_2, "abc %-.i abc", n);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "abc %*.023i abc", 25, n);
  int_test2 = sprintf(str_2, "abc %*.023i abc", 25, n);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "abc %*hi abc", 33, (short)n);
  int_test2 = sprintf(str_2, "abc %*hi abc", 33, (short)n);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "abc %-+i abc", n2);
  int_test2 = sprintf(str_2, "abc %-+i abc", n2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_g) {
  int_test1 = s21_sprintf(str_1, "%g", 2345.4324);
  int_test2 = sprintf(str_2, "%g", 2345.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%23g", 23445.2342);
  int_test2 = sprintf(str_2, "%23g", 23445.2342);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%g%23g", 2345.4324, 23445.2342);
  int_test2 = sprintf(str_2, "%g%23g", 2345.4324, 23445.2342);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%g %23g", 2345.4324, 23445.2342);
  int_test2 = sprintf(str_2, "%g %23g", 2345.4324, 23445.2342);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+#25.8g", 0.0000034);
  int_test2 = sprintf(str_2, "%+#25.8g", 0.0000034);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10.*g", 9, 234567.43242);
  int_test2 = sprintf(str_2, "%-10.*g", 9, 234567.43242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10g", 3456.3424);
  int_test2 = sprintf(str_2, "%-10g", 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%015g", 3456.3424);
  int_test2 = sprintf(str_2, "%015g", 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10g%015g", 1234.234242, 3456.3424);
  int_test2 = sprintf(str_2, "%-10g%015g", 1234.234242, 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10g %015g", 1234.234242, 3456.3424);
  int_test2 = sprintf(str_2, "%-10g %015g", 1234.234242, 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+10.6g", 23456.4324);
  int_test2 = sprintf(str_2, "%+10.6g", 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#*.g", 5, 23456.4324);
  int_test2 = sprintf(str_2, "%#*.g", 5, 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+10.6g %#*.g", 2345.4234, 5, 23456.4324);
  int_test2 = sprintf(str_2, "%+10.6g %#*.g", 2345.4234, 5, 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "dasdad %+10.6g ufiodusfoi34 %#*.g\n",
                          2345.4234, 5, 23456.4324);
  int_test2 = sprintf(str_2, "dasdad %+10.6g ufiodusfoi34 %#*.g\n", 2345.4234,
                      5, 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_G) {
  int_test1 = s21_sprintf(str_1, "%G", 2345.4324);
  int_test2 = sprintf(str_2, "%G", 2345.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%23G", 23445.2342);
  int_test2 = sprintf(str_2, "%23G", 23445.2342);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%G%23G", 2345.4324, 23445.2342);
  int_test2 = sprintf(str_2, "%G%23G", 2345.4324, 23445.2342);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%G %23G", 2345.4324, 23445.2342);
  int_test2 = sprintf(str_2, "%G %23G", 2345.4324, 23445.2342);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+#25.8G", 0.0000034);
  int_test2 = sprintf(str_2, "%+#25.8G", 0.0000034);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10.*G", 9, 234567.43242);
  int_test2 = sprintf(str_2, "%-10.*G", 9, 234567.43242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10G", 3456.3424);
  int_test2 = sprintf(str_2, "%-10G", 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%015G", 3456.3424);
  int_test2 = sprintf(str_2, "%015G", 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10G%015G", 1234.234242, 3456.3424);
  int_test2 = sprintf(str_2, "%-10G%015G", 1234.234242, 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-10G %015G", 1234.234242, 3456.3424);
  int_test2 = sprintf(str_2, "%-10G %015G", 1234.234242, 3456.3424);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+10.6G", 23456.4324);
  int_test2 = sprintf(str_2, "%+10.6G", 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#*.G", 5, 23456.4324);
  int_test2 = sprintf(str_2, "%#*.G", 5, 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+10.6G %#*.G", 2345.4234, 5, 23456.4324);
  int_test2 = sprintf(str_2, "%+10.6G %#*.G", 2345.4234, 5, 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+10.6G%#*.G", 2345.4234, 5, 23456.4324);
  int_test2 = sprintf(str_2, "%+10.6G%#*.G", 2345.4234, 5, 23456.4324);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_E) {
  s21_sprintf(str_1, "abc %E", 0.4784);
  sprintf(str_2, "abc %E", 0.4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %-20E", 0.4784);
  sprintf(str_2, "abc %-20E", 0.4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %+20E", 0.0);
  sprintf(str_2, "abc %+20E", 0.0);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc % 20E", 123456789.123456789);
  sprintf(str_2, "abc % 20E", 123456789.123456789);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %#20E", 1e10);
  sprintf(str_2, "abc %#20E", 1e10);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%+-25.4E", 3456.4325);
  int_test2 = sprintf(str_2, "%+-25.4E", 3456.4325);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%25.*E", 10, 23452.43242);
  int_test2 = sprintf(str_2, "%25.*E", 10, 23452.43242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%-*.10E", 5, -0.05234);
  int_test2 = sprintf(str_2, "%-*.10E", 5, -0.05234);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%25.*E%-*.10E", 10, 23452.43242, 5, -0.05234);
  int_test2 = sprintf(str_2, "%25.*E%-*.10E", 10, 23452.43242, 5, -0.05234);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%25.*E%-*.10E", 10, 23452.43242, 5, -0.05234);
  int_test2 = sprintf(str_2, "%25.*E%-*.10E", 10, 23452.43242, 5, -0.05234);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%#02.E", 25.432523432);
  int_test2 = sprintf(str_2, "%#02.E", 25.432523432);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.*E", 10, 2, 53242.4242);
  int_test2 = sprintf(str_2, "%*.*E", 10, 2, 53242.4242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 =
      s21_sprintf(str_1, "%*.15E%*.*E", 10, 456789.43242, 10, 2, 53242.4242);
  int_test2 =
      sprintf(str_2, "%*.15E%*.*E", 10, 456789.43242, 10, 2, 53242.4242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 =
      s21_sprintf(str_1, "%*.15E %*.*E", 10, 456789.43242, 10, 2, 53242.4242);
  int_test2 =
      sprintf(str_2, "%*.15E %*.*E", 10, 456789.43242, 10, 2, 53242.4242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*.15E", 10, 456789.43242);
  int_test2 = sprintf(str_2, "%*.15E", 10, 456789.43242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%*E", 25, 1111122222.34567899);
  int_test2 = sprintf(str_2, "%*E", 25, 1111122222.34567899);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "%12.16E", 2345678.23453242);
  int_test2 = sprintf(str_2, "%12.16E", 2345678.23453242);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  int_test1 = 0;
  int_test2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_X) {
  s21_sprintf(str_1, "%X", n);
  sprintf(str_2, "%X", n);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%X %X", n, n2);
  sprintf(str_2, "%X %X", n, n2);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%X %X%X", n, n2, n1);
  sprintf(str_2, "%X %X%X", n, n2, n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10X %lX", 21, lg1);
  sprintf(str_2, "%-10X %lX", 21, lg1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%lX", lg1);
  sprintf(str_2, "%lX", lg1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-10X", 21);
  sprintf(str_2, "%-10X", 21);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%10X %-10X", 0, 21);
  sprintf(str_2, "%10X %-10X", 0, 21);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#X %#X", n, n2);
  sprintf(str_2, "%#X %#X", n, n2);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-#10X %#10X", 21, 42);
  sprintf(str_2, "%-#10X %#10X", 21, 42);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-#10X%#10X", 21, 42);
  sprintf(str_2, "%-#10X%#10X", 21, 42);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%-#10X", 21);
  sprintf(str_2, "%-#10X", 21);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#10X", 42);
  sprintf(str_2, "%#10X", 42);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%0#10X", 4221);
  sprintf(str_2, "%0#10X", 4221);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%0#10X", n1);
  sprintf(str_2, "%0#10X", n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%0#10X %0#10X", 4221, n1);
  sprintf(str_2, "%0#10X %0#10X", 4221, n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%0#10X%0#10X", 4221, n1);
  sprintf(str_2, "%0#10X%0#10X", 4221, n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
  sprintf(str_2, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42,
              0, 4221, n1);
  sprintf(str_2, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
          4221, n1);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  s21_sprintf(str_1, "abc %X", 4784);
  sprintf(str_2, "abc %X", 4784);
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_n) {
  int test_int1 = 0;
  int test_int2 = 0;

  int_test1 = s21_sprintf(str_1, "abc %n", &test_int1);
  int_test2 = sprintf(str_2, "abc %n", &test_int2);
  ck_assert_int_eq(test_int1, test_int2);
  ck_assert_int_eq(int_test1, int_test2);
  test_int1 = 0;
  test_int2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "Hello %n Hello", &test_int1);
  int_test2 = sprintf(str_2, "Hello %n Hello", &test_int2);
  ck_assert_int_eq(test_int1, test_int2);
  ck_assert_int_eq(int_test1, int_test2);
  test_int1 = 0;
  test_int2 = 0;
  free_two(str_1, str_2);

  int_test1 = s21_sprintf(str_1, "Hello %n Hello %d", &test_int1, test_int1);
  int_test2 = sprintf(str_2, "Hello %n Hello %d", &test_int2, test_int2);
  ck_assert_int_eq(test_int1, test_int2);
  ck_assert_int_eq(int_test1, int_test2);
  test_int1 = 0;
  test_int2 = 0;
  free_two(str_1, str_2);
}
END_TEST

START_TEST(Sprintf_Test_p) {
  s21_sprintf(str_1, "qwerty");
  sprintf(str_2, "qwerty");
  ck_assert_str_eq(str_1, str_2);
  free_two(str_1, str_2);

  void *p1 = (void *)0x123456789;
  void *p2 = (void *)4325234;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;

  int_test1 = sprintf(str_1, "%p", p1);
  int_test2 = s21_sprintf(str_2, "%p", p1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%20p", p2);
  int_test2 = s21_sprintf(str_2, "%20p", p2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%-15p", p3);
  int_test2 = s21_sprintf(str_2, "%-15p", p3);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%10p", p4);
  int_test2 = s21_sprintf(str_2, "%10p", p4);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%-15p", p2);
  int_test2 = s21_sprintf(str_2, "%-15p", p2);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%*p", 10, p3);
  int_test2 = s21_sprintf(str_2, "%*p", 10, p3);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%10p", p1);
  int_test2 = s21_sprintf(str_2, "%10p", p1);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%*p", 10, p4);
  int_test2 = s21_sprintf(str_2, "%*p", 10, p4);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);

  int_test1 = sprintf(str_1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                      p2, 10, p3, p1, 10, p4);
  int_test2 = s21_sprintf(str_2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3,
                          p4, p2, 10, p3, p1, 10, p4);
  ck_assert_str_eq(str_1, str_2);
  ck_assert_int_eq(int_test1, int_test2);
  free_two(str_1, str_2);
}
END_TEST
START_TEST(sscanf_test_e_1) {
  float e1 = 0, e2 = 0;
  int orig_result = 0, our_result = 0;

  orig_result = sscanf("42e21", "%e", &e1);
  our_result = s21_sscanf("42e21", "%e", &e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("12e21", "%e", &e1);
  our_result = s21_sscanf("12e21", "%e", &e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42.215e-21", "%9e", &e1);
  our_result = s21_sscanf("42.215e-21", "%9e", &e2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "not equal");

  orig_result = sscanf("42.215e21", "%8e", &e1);
  our_result = s21_sscanf("42.215e21", "%8e", &e2);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("1.423422423", "%e", &e1);
  our_result = s21_sscanf("1.423422423", "%e", &e2);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_l_1) {
  int orig_result = 0, our_result = 0;
  unsigned long lu1 = 0, lu2 = 0;
  long ld1 = 0, ld2 = 0;
  wchar_t lc1, lc2;
  wchar_t lsuite[100], ls2[100];

  orig_result = sscanf("a", "%lc", &lc1);
  our_result = s21_sscanf("a", "%lc", &lc2);
  ck_assert_int_eq(lc1, lc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4245", "%lu", &lu1);
  our_result = s21_sscanf("4245", "%lu", &lu2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4245", "%ld", &ld1);
  our_result = s21_sscanf("4245", "%ld", &ld2);
  ck_assert_int_eq(ld1, ld2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("amazing", "%9ls", lsuite);
  our_result = s21_sscanf("amazing", "%9ls", ls2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_int_eq(wcscmp(ls2, lsuite), 0);

  orig_result = sscanf("amazing", "%2ls", lsuite);
  our_result = s21_sscanf("amazing", "%2ls", ls2);
  ck_assert_int_eq(wcscmp(lsuite, ls2), 0);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_L_1) {
  int orig_result = 0, our_result = 0;
  long double Lf1 = 0, Lf2 = 0;

  orig_result = sscanf("42.45", "%Lf", &Lf1);
  our_result = s21_sscanf("42.45", "%Lf", &Lf2);
  ck_assert_msg((int)Lf1 == (int)Lf2, "not equal");
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_u_1) {
  int orig_result = 0, our_result = 0;
  unsigned u1 = 0, u2 = 0;

  orig_result = sscanf("", "%u", &u1);
  our_result = s21_sscanf("", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("481516", "%u", &u1);
  our_result = s21_sscanf("481516", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-48", "%u", &u1);
  our_result = s21_sscanf("-48", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("48.1516", "%u", &u1);
  our_result = s21_sscanf("48.1516", "%u", &u2);
  ck_assert_msg(u1 == u2, "not equal");
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_h_1) {
  int orig_result = 0, our_result = 0;
  unsigned short hu1 = 0, hu2 = 0;

  orig_result = sscanf("1", "%hu", &hu1);
  our_result = s21_sscanf("1", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("48151623", "%hu", &hu1);
  our_result = s21_sscanf("48151623", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-5", "%hu", &hu1);
  our_result = s21_sscanf("-5", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_s_1) {
  int orig_result = 0, our_result = 0;
  char suite[100], s2[100];

  orig_result = sscanf("school 21 Kazan", "%*s%s", suite);
  our_result = s21_sscanf("school 21 Kazan", "%*s%s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("", "%s", suite);
  our_result = s21_sscanf("", "%s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("programming", "%8s", suite);
  our_result = s21_sscanf("programming", "%8s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("programming", "%18s", suite);
  our_result = s21_sscanf("programming", "%18s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_f_1) {
  int orig_result = 0, our_result = 0;
  float f_1 = 0, f2 = 0;

  orig_result = sscanf("42e-3", "%f", &f_1);
  our_result = s21_sscanf("42e-3", "%f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-42.21", "%f", &f_1);
  our_result = s21_sscanf("-42.21", "%f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-21.42", "%5f", &f_1);
  our_result = s21_sscanf("-21.42", "%5f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("21.42", "%5f", &f_1);
  our_result = s21_sscanf("21.42", "%5f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_o_1) {
  int orig_result = 0, our_result = 0;
  unsigned int o1 = 0, o2 = 0;

  orig_result = sscanf("177751", "%o", &o1);
  our_result = s21_sscanf("177751", "%o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("177751", "%3o", &o1);
  our_result = s21_sscanf("177751", "%3o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("123456789", "%5o", &o1);
  our_result = s21_sscanf("123456789", "%5o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("123456789", "%o", &o1);
  our_result = s21_sscanf("123456789", "%o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42.456", "%o", &o1);
  our_result = s21_sscanf("42.456", "%o", &o2);
  ck_assert_uint_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-1", "%o", &o1);
  our_result = s21_sscanf("-1", "%o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_x_1) {
  int orig_result = 0, our_result = 0;
  unsigned x1 = 0, x2 = 0;

  orig_result = sscanf("0X481516", "%x", &x1);
  our_result = s21_sscanf("0X481516", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0x481516", "%2x", &x1);
  our_result = s21_sscanf("0x481516", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("fffff", "%2x", &x1);
  our_result = s21_sscanf("fffff", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("BBBBBB", "%2x", &x1);
  our_result = s21_sscanf("BBBBBB", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("ABCDEFGH", "%x", &x1);
  our_result = s21_sscanf("ABCDEFGH", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("abcdefg", "%x", &x1);
  our_result = s21_sscanf("abcdefg", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0x42456789042456789", "%x", &x1);
  our_result = s21_sscanf("0x42456789042456789", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0", "%x", &x1);
  our_result = s21_sscanf("0", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-42", "%x", &x1);
  our_result = s21_sscanf("-42", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_i_1) {
  int orig_result = 0, our_result = 0;
  int i1 = 0, i2 = 0;

  orig_result = sscanf("9878645", "%i", &i1);
  our_result = s21_sscanf("9878645", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0x42AB", "%i", &i1);
  our_result = s21_sscanf("0x42AB", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("177777777", "%i", &i1);
  our_result = s21_sscanf("177777777", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-481516", "%i", &i1);
  our_result = s21_sscanf("-481516", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_proc_1) {
  int orig_result = 0, our_result = 0;
  char proc1[100] = {0}, proc2[100] = {0};

  orig_result = sscanf("48151642342", "%s%%", proc1);
  our_result = s21_sscanf("48151642342", "%s%%", proc2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("Hello", "%%%s", proc1);
  our_result = s21_sscanf("Hello", "%%%s", proc2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_p_1) {
  int orig_result = 0, our_result = 0;
  void *p1 = 0, *p2 = 0;

  orig_result = sscanf("0x42", "%8p", &p1);
  our_result = s21_sscanf("0x42", "%8p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0X4245", "%p", &p1);
  our_result = s21_sscanf("0X4245", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0X4245AB", "%p", &p1);
  our_result = s21_sscanf("0X4245AB", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42.456", "%p", &p1);
  our_result = s21_sscanf("42.456", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-5", "%8p", &p1);
  our_result = s21_sscanf("-5", "%8p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0", "%p", &p1);
  our_result = s21_sscanf("0", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_n_1) {
  int n_1 = 0, n_2 = 0, d_1 = 0, d_2 = 0, orig_result = 0, our_result = 0;

  orig_result = sscanf("42.456", "%n", &n_1);
  our_result = s21_sscanf("42.456", "%n", &n_2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42456", "%d%n", &d_1, &n_1);
  our_result = s21_sscanf("42456", "%d%n", &d_2, &n_2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_d_1) {
  int orig_result = 0, our_result = 0, d1 = 0, d2 = 0;

  orig_result = sscanf("42", "%d", &d1);
  our_result = s21_sscanf("42", "%d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-42 l", "%10d", &d1);
  our_result = s21_sscanf("-42 l", "%10d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_all) {
  int d1 = 0, d2 = 0, i1 = 0, i2 = 0, n_1 = 0, n_2 = 0, orig_result = 0,
      our_result = 0;
  float e1 = 0, e2 = 0, E1 = 0, E2 = 0, f_1 = 0, f2 = 0, g1 = 0, g2 = 0, G1 = 0,
        G2 = 0;
  unsigned o1 = 0, o2 = 0, u1 = 0, u2 = 0, x1 = 0, x2 = 0, X1 = 0, X2 = 0;
  void *p1 = 0, *p2 = 0;
  char suite[100], s2[100], c1, c2, proc1[100] = {0}, proc2[100] = {0};
  short hi1 = 0, hi2 = 0, hd1 = 0, hd2 = 0;
  unsigned long lo1 = 0, lo2 = 0, lu1 = 0, lu2 = 0;
  long double Le1 = 0, Le2 = 0, LE1 = 0, LE2 = 0, Lg1 = 0, Lg2 = 0, LG1 = 0,
              LG2 = 0;

  orig_result = sscanf("42", "%d", &d1);
  our_result = s21_sscanf("42", "%d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42 amazing", "%d%9s", &d1, suite);
  our_result = s21_sscanf("42 amazing", "%d%9s", &d2, s2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42 amazing q", "%d%9s%c", &d1, suite, &c1);
  our_result = s21_sscanf("42 amazing q", "%d%9s%c", &d2, s2, &c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q", "%i%d%9s%c", &i1, &d1, suite, &c1);
  our_result = s21_sscanf("4 42 amazing q", "%i%d%9s%c", &i2, &d2, s2, &c2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21", "%i%d%9s%c%e", &i1, &d1, suite, &c1, &e1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21", "%i%d%9s%c%e", &i2, &d2, s2, &c2, &e2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12 43e21", "%i%d%9s%c%e%E", &i1, &d1,
                       suite, &c1, &e1, &E1);
  our_result = s21_sscanf("4 42 amazing q 12 43e21", "%i%d%9s%c%e%E", &i2, &d2,
                          s2, &c2, &e2, &E2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37", "%i%d%9s%c%e%E%f",
                       &i1, &d1, suite, &c1, &e1, &E1, &f_1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13,37", "%i%d%9s%c%e%E%f",
                          &i2, &d2, s2, &c2, &e2, &E2, &f2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21 43e21 13.37 2.28", "%i%d%9s%c%e%E%f%g", &i1,
             &d1, suite, &c1, &e1, &E1, &f_1, &g1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28", "%i%d%9s%c%e%E%f%g",
                 &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                       "%i%d%9s%c%e%E%f%g%G", &i1, &d1, suite, &c1, &e1, &E1,
                       &f_1, &g1, &G1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                          "%i%d%9s%c%e%E%f%g%G", &i2, &d2, s2, &c2, &e2, &E2,
                          &f2, &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                       "%i%d%9s%c%e%E%f%g%G", &i1, &d1, suite, &c1, &e1, &E1,
                       &f_1, &g1, &G1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                          "%i%d%9s%c%e%E%f%g%G", &i2, &d2, s2, &c2, &e2, &E2,
                          &f2, &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101",
                       "%i%d%9s%c%e%E%f%g%G%o", &i1, &d1, suite, &c1, &e1, &E1,
                       &f_1, &g1, &G1, &o1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101",
                          "%i%d%9s%c%e%E%f%g%G%o", &i2, &d2, s2, &c2, &e2, &E2,
                          &f2, &g2, &G2, &o2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854",
             "%i%d%9s%c%e%E%f%g%G%o%u", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
             &g1, &G1, &o1, &u1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854",
                 "%i%d%9s%c%e%E%f%g%G%o%u", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                 &g2, &G2, &o2, &u2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab",
             "%i%d%9s%c%e%E%f%g%G%o%u%x", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
             &g1, &G1, &o1, &u1, &x1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab",
                 "%i%d%9s%c%e%E%f%g%G%o%u%x", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                 &g2, &G2, &o2, &u2, &x2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X", &i1, &d1, suite, &c1, &e1, &E1, &f_1, &g1,
      &G1, &o1, &u1, &x1, &X1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X", &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2, &G2,
      &o2, &u2, &x2, &X2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p1", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
      &g1, &G1, &o1, &u1, &x1, &X1, &p1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p2", &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2,
      &G2, &o2, &u2, &x2, &X2, &p2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab "
      "BA21 shrek & amazing is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%%", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
      &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%%", &i2, &d2, s2, &c2, &e2, &E2, &f2,
      &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(orig_result, our_result);
  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab "
      "BA21 shrek & amazing is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%9s%%", &i1, &d1, suite, &c1, &e1, &E1,
      &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1, proc1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab "
      "BA21 shrek & amazing is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%9s%%", &i2, &d2, s2, &c2, &e2, &E2, &f2,
      &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2, proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = s21_sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%12i%4d%20s%c%3e%7E%1f%9g%5G%6o%12u%11x%2X%10p%n%21s%%", &i1, &d1, suite,
      &c1, &e1, &E1, &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1, proc1);
  our_result = s21_sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%12i%4d%20s%c%3e%7E%1f%9g%5G%6o%12u%11x%2X%10p%n%21s%%", &i2, &d2, s2,
      &c2, &e2, &E2, &f2, &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2, proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg((int)E1 == (int)E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 "
      "shrek & amazing is sus?",
      "%*i%12i%4d%20s%c%3e%7E%*i%1f%9g%5G%6o%12u%*x%11x%2X%10p%n%21s%%", &i1,
      &d1, suite, &c1, &e1, &E1, &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1,
      proc1);
  our_result = s21_sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%*i%12i%4d%20s%c%3e%7E%*i%1f%9g%5G%6o%12u%*x%11x%2X%10p%n%21s%%", &i2,
      &d2, s2, &c2, &e2, &E2, &f2, &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2,
      proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%*i%12hi%4hd%20s%c%3Le%7LE%*i%1f%9Lg%5LG%6lo%12lu%*x%11x%2X%10p%n%21s%%",
      &hi1, &hd1, suite, &c1, &Le1, &LE1, &f_1, &Lg1, &LG1, &lo1, &lu1, &x1,
      &X1, &p1, &n_1, proc1);
  our_result = s21_sscanf(
      "4 42 amazingq f12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%*i%12hi%4hd%20s%c%3Le%7LE%*i%1f%9Lg%5LG%6lo%12lu%*x%11x%2X%10p%n%21s%%",
      &hi2, &hd2, s2, &c2, &Le2, &LE2, &f2, &Lg2, &LG2, &lo2, &lu2, &x2, &X2,
      &p2, &n_2, proc2);
  ck_assert_int_eq(hi1, hi2);
  ck_assert_int_eq(hd1, hd2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(lo1, lo2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_c_1) {
  char *empty_str = "";
  char c1, c2;
  int orig_result, our_result;
  char *storig_result = " abc ";

  orig_result = sscanf(storig_result, "%*c%*c%c", &c1);
  our_result = s21_sscanf(storig_result, "%*c%*c%c", &c2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_int_eq(c1, c2);

  orig_result = sscanf(empty_str, "%c", &c1);
  our_result = s21_sscanf(empty_str, "%c", &c2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_int_eq(c1, c2);

  char fstr[] = "%c %c %c %c";
  char str[] = " c    a  d b";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, z1 = 0, z2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &z1, &d1);

  int res2 = sscanf(str, fstr, &a2, &b2, &z2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(z1, z2);
  ck_assert_int_eq(d1, d2);

  char fstr1[] = "%c%c%c%c";
  char str1[] = "cadb";
  a1 = 0, a2 = 2, b1 = 0, b2 = 2, z1 = 0, z2 = 1, d1 = 0, d2 = 3;

  res1 = s21_sscanf(str1, fstr1, &a1, &b1, &z1, &d1);

  res2 = sscanf(str1, fstr1, &a2, &b2, &z2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(z1, z2);
  ck_assert_int_eq(d1, d2);

  char fstr3[] = "%c %c %c %c";
  char str3[] = "   0 000    ";
  a1 = 0, a2 = 2, b1 = 0, b2 = 2, z1 = 0, z2 = 1, d1 = 0, d2 = 3;

  res1 = s21_sscanf(str3, fstr3, &a1, &b1, &z1, &d1);

  res2 = sscanf(str3, fstr3, &a2, &b2, &z2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(z1, z2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_test_d_2) {
  char *empty_str = "";
  int nmb1 = 111, nmb2 = 111;
  int orig_result, our_result;
  char *stour_result = "  42   -42   567  32368  ";
  char wrong_stour_result[] = " abc 324 ";
  orig_result = sscanf(stour_result, "%*d%d%*d%*d", &nmb1);
  our_result = s21_sscanf(stour_result, "%*d%d%*d%*d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(orig_result, our_result);

  nmb1 = 1, nmb2 = 1;
  orig_result = sscanf(empty_str, "%d", &nmb1);
  our_result = s21_sscanf(empty_str, "%d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(orig_result, our_result);

  nmb1 = 0, nmb2 = 0;
  orig_result = sscanf(wrong_stour_result, "%d", &nmb1);
  our_result = s21_sscanf(wrong_stour_result, "%d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_i_2) {
  char *empty_str = "";
  int nmbX1 = 1, nmbX2 = 1;
  int nmbO1 = 1, nmbO2 = 1;
  int nmbD1 = 1, nmbD2 = 1;
  int orig_result, our_result;
  char *str3 = "  0x3F5  0600 -4245 987";
  char *wrong_str3 = "  0000xFF5  ";

  orig_result = sscanf(str3, "%i%i%i%*i", &nmbX1, &nmbO1, &nmbD1);
  our_result = s21_sscanf(str3, "%i%i%i%*i", &nmbX2, &nmbO2, &nmbD2);
  ck_assert_int_eq(nmbX1, nmbX2);
  ck_assert_int_eq(nmbO1, nmbO2);
  ck_assert_int_eq(nmbD1, nmbD2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%i", &nmbD1);
  our_result = s21_sscanf(empty_str, "%i", &nmbD2);
  ck_assert_int_eq(nmbD1, nmbD2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str3, "%i", &nmbX1);
  our_result = s21_sscanf(wrong_str3, "%i", &nmbX2);
  ck_assert_uint_eq(nmbX1, nmbX2);
  ck_assert_int_eq(orig_result, our_result);

  unsigned int octnmb1 = 1, octnmb2 = 2;

  orig_result = sscanf(str3, "%*x%o", &octnmb1);
  our_result = s21_sscanf(str3, "%*x%o", &octnmb2);
  ck_assert_uint_eq(octnmb1, octnmb2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_u_2) {
  char *empty_str = "";
  unsigned u1 = 1, u2 = 2, orig_result, our_result;
  char *str4 = " 0    3513187186";
  char *wrong_str4 = "  School21";

  orig_result = sscanf(str4, "%*u%u", &u1);
  our_result = s21_sscanf(str4, "%*u%u", &u2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%u", &u1);
  our_result = s21_sscanf(empty_str, "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str4, "%u", &u1);
  our_result = s21_sscanf(wrong_str4, "%u", &u2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_x_2) {
  unsigned u1 = 1, u2 = 2, u3 = 3, u4 = 4, orig_result, our_result;
  char *str4 = " 4242  322662 42 42";

  orig_result = sscanf(str4, "%*x%x%X%*X", &u1, &u3);
  our_result = s21_sscanf(str4, "%*x%x%X%*X", &u2, &u4);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_double) {
  char *empty_str = "";
  int orig_result, our_result;
  double fl1 = 1, fl2 = 2;
  double dbl1 = 1, dbl2 = 2;
  char *str5 = "  -876.214235  2145.93560721567  324.21427 ";
  char *wrong_str5 = "  School21.42";

  orig_result = sscanf(str5, "%lf%lf%*f", &fl1, &dbl1);
  our_result = s21_sscanf(str5, "%lf%lf%*f", &fl2, &dbl2);
  ck_assert_msg(dbl1 != dbl2, "Float test 1 fail");
  ck_assert_msg(fl1 != fl2, "Float test 2 fail");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%lf", &dbl1);
  our_result = s21_sscanf(empty_str, "%lf", &dbl2);
  ck_assert_float_eq(dbl1, dbl2);
  ck_assert_msg(dbl1 != dbl2, "Float test 3 fail");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str5, "%lf", &dbl1);
  our_result = s21_sscanf(wrong_str5, "%lf", &dbl2);
  ck_assert_float_eq(dbl1, dbl2);
  ck_assert_msg(dbl1 != dbl2, "Float test 4 fail");
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_EeGg) {
  char *empty_str = "";
  int orig_result, our_result;
  double e1, e2, g1, g2;
  char *str6_u = "  0.08762147E+03  1446567457.024E-11 0E+02";
  char *wrong_str6 = "  School21+02";

  orig_result = sscanf(str6_u, "%lE%lG%*e", &e1, &g1);
  our_result = s21_sscanf(str6_u, "%lE%lG%*e", &e2, &g2);
  ck_assert_int_eq(e1, e2);
  ck_assert_int_eq(g1, g2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%le", &e1);
  our_result = s21_sscanf(empty_str, "%le", &e2);
  ck_assert_int_eq(e1, e2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str6, "%lg", &g1);
  our_result = s21_sscanf(wrong_str6, "%lg", &g2);
  ck_assert_int_eq(g1, g2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_s_2) {
  int orig_result, our_result;
  char str_vaorig_result[30] = "", str_vaour_result[30] = "";

  orig_result =
      sscanf(" this is random string", "%*s%*s%10s%*s", str_vaorig_result);
  our_result =
      s21_sscanf(" this is random string", "%*s%*s%10s%*s", str_vaour_result);
  ck_assert_str_eq(str_vaorig_result, str_vaour_result);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("\0", "%10s", str_vaorig_result);
  our_result = s21_sscanf("\0", "%10s", str_vaour_result);
  ck_assert_str_eq(str_vaorig_result, str_vaour_result);
  ck_assert_int_eq(orig_result, our_result);
}

START_TEST(sscanf_test_ld) {
  char *empty_str = "";
  int orig_result, our_result;
  long nm1 = 111, nm2 = 111;
  char *str5 = "  42   -5424242   567  588  ";
  char wrong_str5[] = " abc 42 ";

  orig_result = sscanf(str5, "%*d%ld%*d%*d", &nm1);
  our_result = s21_sscanf(str5, "%*d%ld%*d%*d", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%ld", &nm1);
  our_result = s21_sscanf(empty_str, "%ld", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str5, "%ld", &nm1);
  our_result = s21_sscanf(wrong_str5, "%ld", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_hd) {
  char *empty_str = "";
  int orig_result, our_result;
  short nh1 = 111, nh2 = 111;
  char *str6 = "  42   -5424242   567  588  ";
  char wrong_str6[] = " abc 42 ";

  orig_result = sscanf(str6, "%*d%hd%*d%*d", &nh1);
  our_result = s21_sscanf(str6, "%*d%hd%*d%*d", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%hd", &nh1);
  our_result = s21_sscanf(empty_str, "%hd", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str6, "%hd", &nh1);
  our_result = s21_sscanf(wrong_str6, "%hd", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_lu) {
  char *empty_str = "";
  int orig_result, our_result;
  unsigned long nu1 = 111, nu2 = 111;
  char *str7 = "  42   5424242   567  588  ";
  char wrong_str7[] = " abc 42 ";

  orig_result = sscanf(str7, "%*d%lu%*d%*d", &nu1);
  our_result = s21_sscanf(str7, "%*d%lu%*d%*d", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%lu", &nu1);
  our_result = s21_sscanf(empty_str, "%lu", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str7, "%lu", &nu1);
  our_result = s21_sscanf(wrong_str7, "%lu", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_hu) {
  char *empty_str = "";
  int orig_result, our_result;
  unsigned short nuh1 = 111, nuh2 = 111;
  char *str5 = "  42   15000   567  588  ";
  char wrong_str5[] = " abc 42 ";

  orig_result = sscanf(str5, "%*d%hu%*d%*d", &nuh1);
  our_result = s21_sscanf(str5, "%*d%hu%*d%*d", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%hu", &nuh1);
  our_result = s21_sscanf(empty_str, "%hu", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str5, "%hu", &nuh1);
  our_result = s21_sscanf(wrong_str5, "%hu", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_ptr) {
  char *empty_str = "";
  int orig_result, our_result;
  unsigned long p1 = 111, p2 = 111;
  unsigned long *ptorig_result = &p1;
  unsigned long *ptorig_result1 = &p1;
  unsigned long *ptour_result = &p2;
  unsigned long *ptour_result2 = &p2;
  char *str8 = "  42   5424242   0x567  588  ";
  char wrong_str8[] = " abc 42 ";

  orig_result = sscanf(str8, "%*d%p%p%*p", &ptorig_result, &ptorig_result1);
  our_result = s21_sscanf(str8, "%*d%p%p%*p", &ptour_result, &ptour_result2);
  ck_assert_ptr_eq(ptorig_result, ptour_result);
  ck_assert_ptr_eq(ptorig_result1, ptour_result2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%p", &ptorig_result);
  our_result = s21_sscanf(empty_str, "%p", &ptour_result);
  ck_assert_ptr_eq(ptorig_result, ptour_result);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str8, "%p", &ptorig_result);
  our_result = s21_sscanf(wrong_str8, "%p", &ptour_result);
  ck_assert_ptr_eq(ptorig_result, ptour_result);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

int main(void) {
  Suite *suite =
      suite_create("S21_TEST");  // создание наборов тестов и с именем S21_TEST
  SRunner *srunner = srunner_create(suite);

  TCase *strlen_test =
      tcase_create("Strlen");  // создание тестового примера с именем StrLen
  suite_add_tcase(suite, strlen_test);  // добавление в тестовый набор
  tcase_add_test(strlen_test,
                 StrLen_Test);  // добавление тестовой функции в тестовый пример

  TCase *strcat_test = tcase_create("Strcat");
  suite_add_tcase(suite, strcat_test);
  tcase_add_test(strcat_test, StrCat_Test);

  TCase *strcmp_test = tcase_create("Strcmp");
  suite_add_tcase(suite, strcmp_test);
  tcase_add_test(strcmp_test, StrCmp_Test);

  TCase *strncat_test = tcase_create("Strncat");
  suite_add_tcase(suite, strncat_test);
  tcase_add_test(strncat_test, StrnCat_Test);

  TCase *strncmp_test = tcase_create("Strncmp");
  suite_add_tcase(suite, strncmp_test);
  tcase_add_test(strncmp_test, StrnCmp_Test);

  TCase *memcmp_test = tcase_create("Memcmp");
  suite_add_tcase(suite, memcmp_test);
  tcase_add_test(memcmp_test, MemCmp_Test);

  TCase *memset_test = tcase_create("Memset");
  suite_add_tcase(suite, memset_test);
  tcase_add_test(memset_test, MemSet_Test);

  TCase *memcpy_test = tcase_create("Memcpy");
  suite_add_tcase(suite, memcpy_test);
  tcase_add_test(memcpy_test, MemCpy_Test);

  TCase *memmove_test = tcase_create("Memmove");
  suite_add_tcase(suite, memmove_test);
  tcase_add_test(memmove_test, MemMove_Test);

  TCase *memchr_test = tcase_create("Memchr");
  suite_add_tcase(suite, memchr_test);
  tcase_add_test(memchr_test, MemChr_Test);

  TCase *strerror_test = tcase_create("Strerror");
  suite_add_tcase(suite, strerror_test);
  tcase_add_test(strerror_test, StrError_Test);

  TCase *strchr_test = tcase_create("Strchr");
  suite_add_tcase(suite, strchr_test);
  tcase_add_test(strchr_test, StrChr_Test);

  TCase *strrchr_test = tcase_create("Strrchr");
  suite_add_tcase(suite, strrchr_test);
  tcase_add_test(strrchr_test, StrrChr_Test);

  TCase *strcspn_test = tcase_create("Strcspn");
  suite_add_tcase(suite, strcspn_test);
  tcase_add_test(strcspn_test, StrcSpn_Test);

  TCase *strspn_test = tcase_create("Strspn");
  suite_add_tcase(suite, strspn_test);
  tcase_add_test(strspn_test, StrSpn_Test);

  TCase *strpbrk_test = tcase_create("Strpbrk");
  suite_add_tcase(suite, strpbrk_test);
  tcase_add_test(strpbrk_test, StrPbrk_Test);

  TCase *strstr_test = tcase_create("Strstr");
  suite_add_tcase(suite, strstr_test);
  tcase_add_test(strstr_test, StrStr_Test);

  TCase *strcpy_test = tcase_create("Strcpy");
  suite_add_tcase(suite, strcpy_test);
  tcase_add_test(strcpy_test, StrCpy_Test);

  TCase *strncpy_test = tcase_create("Strncpy");
  suite_add_tcase(suite, strncpy_test);
  tcase_add_test(strncpy_test, StrnCpy_Test);

  TCase *strtok_test = tcase_create("Strtok");
  suite_add_tcase(suite, strtok_test);
  tcase_add_test(strtok_test, StrTok_Test);

  TCase *to_up_test = tcase_create("To_up");
  suite_add_tcase(suite, to_up_test);
  tcase_add_test(to_up_test, To_Up_Test);

  TCase *to_low_test = tcase_create("To_low");
  suite_add_tcase(suite, to_low_test);
  tcase_add_test(to_low_test, To_Low_Test);

  TCase *insert_test = tcase_create("Insert");
  suite_add_tcase(suite, insert_test);
  tcase_add_test(insert_test, Insert_Test);

  TCase *trim_test = tcase_create("Trim");
  suite_add_tcase(suite, trim_test);
  tcase_add_test(trim_test, Trim_Test);

  TCase *atoi_test = tcase_create("Atoi");
  suite_add_tcase(suite, atoi_test);
  tcase_add_test(atoi_test, Atoi_Test);

  TCase *sprintf_d_test = tcase_create("Sprnt_d");
  suite_add_tcase(suite, sprintf_d_test);
  tcase_add_test(sprintf_d_test, Sprintf_Test_d);

  TCase *sprintf_i_test = tcase_create("Sprnt_i");
  suite_add_tcase(suite, sprintf_i_test);
  tcase_add_test(sprintf_i_test, Sprintf_Test_i);

  TCase *sprintf_c_test = tcase_create("Sprnt_c");
  suite_add_tcase(suite, sprintf_c_test);
  tcase_add_test(sprintf_c_test, Sprintf_Test_c);

  TCase *sprintf_s_test = tcase_create("Sprnt_s");
  suite_add_tcase(suite, sprintf_s_test);
  tcase_add_test(sprintf_s_test, Sprintf_Test_s);

  TCase *sprintf_f = tcase_create("Sprnt_f");
  suite_add_tcase(suite, sprintf_f);
  tcase_add_test(sprintf_f, Sprintf_Test_f);

  TCase *sprintf_u_test = tcase_create("Sprnt_u");
  suite_add_tcase(suite, sprintf_u_test);
  tcase_add_test(sprintf_u_test, Sprintf_Test_u);

  TCase *sprintf_g = tcase_create("Sprnt_g");
  suite_add_tcase(suite, sprintf_g);
  tcase_add_test(sprintf_g, Sprintf_Test_g);

  TCase *sprintf_G_test = tcase_create("Sprnt_G");
  suite_add_tcase(suite, sprintf_G_test);
  tcase_add_test(sprintf_G_test, Sprintf_Test_G);

  TCase *sprintf_e_test = tcase_create("Sprnt_e");
  suite_add_tcase(suite, sprintf_e_test);
  tcase_add_test(sprintf_e_test, Sprintf_Test_e);

  TCase *sprintf_E_test = tcase_create("Sprnt_E");
  suite_add_tcase(suite, sprintf_E_test);
  tcase_add_test(sprintf_E_test, Sprintf_Test_E);

  TCase *sprintf_x_test = tcase_create("Sprnt_x");
  suite_add_tcase(suite, sprintf_x_test);
  tcase_add_test(sprintf_x_test, Sprintf_Test_x);

  TCase *sprintf_X_test = tcase_create("Sprnt_X");
  suite_add_tcase(suite, sprintf_X_test);
  tcase_add_test(sprintf_X_test, Sprintf_Test_X);

  TCase *sprintf_o_test = tcase_create("Sprnt_o");
  suite_add_tcase(suite, sprintf_o_test);
  tcase_add_test(sprintf_o_test, Sprintf_Test_o);

  TCase *sprintf_n_test = tcase_create("Sprnt_n");
  suite_add_tcase(suite, sprintf_n_test);
  tcase_add_test(sprintf_n_test, Sprintf_Test_n);

  TCase *sprintf_p_test = tcase_create("Sprnt_p");
  suite_add_tcase(suite, sprintf_p_test);
  tcase_add_test(sprintf_p_test, Sprintf_Test_p);
  TCase *s21_Sscanf_e = tcase_create("Sscanf_e");
  suite_add_tcase(suite, s21_Sscanf_e);
  tcase_add_test(s21_Sscanf_e, sscanf_test_e_1);

  TCase *s21_Sscanf_EeGg = tcase_create("Sscanf_EeGg");
  suite_add_tcase(suite, s21_Sscanf_EeGg);
  tcase_add_test(s21_Sscanf_EeGg, sscanf_test_EeGg);

  TCase *s21_Sscanf_l_1 = tcase_create("Sscanf_l");
  suite_add_tcase(suite, s21_Sscanf_l_1);
  tcase_add_test(s21_Sscanf_l_1, sscanf_test_l_1);

  TCase *s21_Sscanf_L_1 = tcase_create("Sscanf_L");
  suite_add_tcase(suite, s21_Sscanf_L_1);
  tcase_add_test(s21_Sscanf_L_1, sscanf_test_L_1);

  TCase *s21_Sscanf_ld = tcase_create("Sscanf_ld");
  suite_add_tcase(suite, s21_Sscanf_ld);
  tcase_add_test(s21_Sscanf_ld, sscanf_test_ld);

  TCase *s21_Sscanf_hd = tcase_create("Sscanf_hd");
  suite_add_tcase(suite, s21_Sscanf_hd);
  tcase_add_test(s21_Sscanf_hd, sscanf_test_hd);

  TCase *s21_Sscanf_lu = tcase_create("Sscanf_lu");
  suite_add_tcase(suite, s21_Sscanf_lu);
  tcase_add_test(s21_Sscanf_lu, sscanf_test_lu);

  TCase *s21_Sscanf_hu = tcase_create("Sscanf_hu");
  suite_add_tcase(suite, s21_Sscanf_hu);
  tcase_add_test(s21_Sscanf_hu, sscanf_test_hu);

  TCase *s21_Sscanf_h_1 = tcase_create("Sscanf_h");
  suite_add_tcase(suite, s21_Sscanf_h_1);
  tcase_add_test(s21_Sscanf_h_1, sscanf_test_h_1);

  TCase *s21_Sscanf_d_1 = tcase_create("Sscanf_d");
  suite_add_tcase(suite, s21_Sscanf_d_1);
  tcase_add_test(s21_Sscanf_d_1, sscanf_test_d_1);

  TCase *s21_Sscanf_d_2 = tcase_create("Sscanf_d");
  suite_add_tcase(suite, s21_Sscanf_d_2);
  tcase_add_test(s21_Sscanf_d_2, sscanf_test_d_2);

  TCase *s21_Sscanf_u_1 = tcase_create("Sscanf_u");
  suite_add_tcase(suite, s21_Sscanf_u_1);
  tcase_add_test(s21_Sscanf_u_1, sscanf_test_u_1);

  TCase *s21_Sscanf_u_2 = tcase_create("Sscanf_u");
  suite_add_tcase(suite, s21_Sscanf_u_2);
  tcase_add_test(s21_Sscanf_u_2, sscanf_test_u_2);

  TCase *s21_Sscanf_ptr = tcase_create("Sscanf_ptr");
  suite_add_tcase(suite, s21_Sscanf_ptr);
  tcase_add_test(s21_Sscanf_ptr, sscanf_test_ptr);

  TCase *s21_Sscanf_proc = tcase_create("Sscanf_proc");
  suite_add_tcase(suite, s21_Sscanf_proc);
  tcase_add_test(s21_Sscanf_proc, sscanf_test_proc_1);

  TCase *s21_Sscanf_p_1 = tcase_create("s21_Sscanf_p");
  suite_add_tcase(suite, s21_Sscanf_p_1);
  tcase_add_test(s21_Sscanf_p_1, sscanf_test_p_1);

  TCase *s21_Sscanf_s_1 = tcase_create("Sscanf_s");
  suite_add_tcase(suite, s21_Sscanf_s_1);
  tcase_add_test(s21_Sscanf_s_1, sscanf_test_s_1);

  TCase *s21_Sscanf_s_2 = tcase_create("Sscanf_s");
  suite_add_tcase(suite, s21_Sscanf_s_2);
  tcase_add_test(s21_Sscanf_s_2, sscanf_test_s_2);

  TCase *s21_Sscanf_f_1 = tcase_create("Sscanf_f");
  suite_add_tcase(suite, s21_Sscanf_f_1);
  tcase_add_test(s21_Sscanf_f_1, sscanf_test_f_1);

  TCase *s21_Sscanf_o_1 = tcase_create("Sscanf_o");
  suite_add_tcase(suite, s21_Sscanf_o_1);
  tcase_add_test(s21_Sscanf_o_1, sscanf_test_o_1);

  TCase *s21_Sscanf_x_1 = tcase_create("Sscanf_x");
  suite_add_tcase(suite, s21_Sscanf_x_1);
  tcase_add_test(s21_Sscanf_x_1, sscanf_test_x_1);

  TCase *s21_Sscanf_x_2 = tcase_create("Sscanf_x");
  suite_add_tcase(suite, s21_Sscanf_x_2);
  tcase_add_test(s21_Sscanf_x_2, sscanf_test_x_2);

  TCase *s21_Sscanf_i_1 = tcase_create("Sscanf_i");
  suite_add_tcase(suite, s21_Sscanf_i_1);
  tcase_add_test(s21_Sscanf_i_1, sscanf_test_i_1);

  TCase *s21_Sscanf_i_2 = tcase_create("Sscanf_i");
  suite_add_tcase(suite, s21_Sscanf_i_2);
  tcase_add_test(s21_Sscanf_i_2, sscanf_test_i_2);

  TCase *s21_Sscanf_c_1 = tcase_create("Sscanf_c");
  suite_add_tcase(suite, s21_Sscanf_c_1);
  tcase_add_test(s21_Sscanf_c_1, sscanf_test_c_1);

  TCase *s21_Sscanf_n_1 = tcase_create("Sscanf_n");
  suite_add_tcase(suite, s21_Sscanf_n_1);
  tcase_add_test(s21_Sscanf_n_1, sscanf_test_n_1);

  TCase *s21_Sscanf_test_double = tcase_create("Sscanf_double");
  suite_add_tcase(suite, s21_Sscanf_test_double);
  tcase_add_test(s21_Sscanf_test_double, sscanf_test_double);

  TCase *s21_Sscanf_all = tcase_create("Sscanf_all");
  suite_add_tcase(suite, s21_Sscanf_all);
  tcase_add_test(s21_Sscanf_all, sscanf_test_all);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
