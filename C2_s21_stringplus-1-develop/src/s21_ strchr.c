#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int i = 0;
  char *res = s21_NULL;
  while (str[i] && str[i] != c) {
    i++;
  }
  if (c == str[i]) {
    res = (char *)str + i;
  }
  return res;
}
