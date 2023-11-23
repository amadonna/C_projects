#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  int stop = 0;
  s21_size_t index = 0;
  while (index < s21_strlen(str1) && stop != 1) {
    s21_size_t j = 0;
    s21_size_t check = 0;
    while (j < s21_strlen(str2) && !check) {
      if (str1[index] == str2[j]) check = 1;
      j++;
    }
    if (!check) stop = 1;
    if (check) index++;
  }
  return index;
}