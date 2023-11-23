#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int i = 0;
  int l = (int)s21_strlen(dest);
  for (; i < (int)n; i++) {
    dest[l + i] = src[i];
  }
  dest[l + i + 1] = '\0';
  return dest;
}
