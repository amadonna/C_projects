#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int stop = 0;
  s21_size_t len = 0;
  while (str1[len] != '\0' && stop != 1) {
    int j = 0;
    while (str2[j] != '\0' && stop != 1) {
      if (str1[len] == str2[j]) {
        stop = 1;
      }
      j++;
    }
    len++;
  }
  len -= stop == 1 ? 1 : 0;
  return len;
}
