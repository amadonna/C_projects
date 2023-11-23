#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int check = 0;
  unsigned char *byte = (unsigned char *)str;
  for (s21_size_t i = 0; i < n && check == 0; i++) {
    if (*byte == (unsigned char)c)
      check = 1;
    else
      byte++;
  }
  return check > 0 ? byte : s21_NULL;
}
