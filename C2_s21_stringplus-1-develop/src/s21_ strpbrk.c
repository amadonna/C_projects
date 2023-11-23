#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *rez = (char *)str1;
  int stop = 0;
  s21_size_t len = 0;
  while (str1[len] != '\0' && stop != 1) {
    int j = 0;
    while (stop != 1 && str2[j] != '\0') {
      if (str1[len] == str2[j]) stop = 1;
      j++;
    }
    len++;
  }
  if (stop == 1) {
    rez += len - 1;
  }
  return stop > 0 ? rez : s21_NULL;
}
