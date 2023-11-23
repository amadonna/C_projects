#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  char *byte1 = (char *)str1;
  char *byte2 = (char *)str2;
  for (s21_size_t i = 0; i < n && res == 0; i++) {
    if (byte1[i] != byte2[i]) res = byte1[i] - byte2[i];
  }
  return res;
}
