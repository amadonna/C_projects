#include "s21_string.h"

void *s21_memcpy(void *dst, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    ((char *)dst)[i] = ((char *)src)[i];
  }
  return dst;
}
