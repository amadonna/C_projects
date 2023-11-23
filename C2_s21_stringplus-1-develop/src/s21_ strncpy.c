#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int i = 0;
  for (; i < (int)n; i++) {
    dest[i] = src[i];
  }
  return dest;
}
