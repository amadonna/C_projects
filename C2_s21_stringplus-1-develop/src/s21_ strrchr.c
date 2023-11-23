#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ret = s21_NULL;
  int stop = 0;
  int i = (int)s21_strlen(str);
  while (i >= 0 && stop != 1) {
    if (c == str[i]) {
      stop = 1;
    }
    i--;
  }
  if (stop == 1) ret = (char *)str + i + 1;
  return ret;
}
