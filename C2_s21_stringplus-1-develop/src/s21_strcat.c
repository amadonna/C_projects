#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  // printf("len des = %ld\n", s21_strlen(dest));
  int i = 0;
  int l = (int)s21_strlen(dest);
  for (; src[i] != '\0'; i++) {
    dest[l + i] = src[i];
  }
  dest[l + i] = '\0';
  return dest;
}
