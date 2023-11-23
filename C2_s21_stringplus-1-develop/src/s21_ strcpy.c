#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  for (; i < (int)s21_strlen(src); i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}
