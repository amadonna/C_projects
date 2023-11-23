#include "s21_string.h"

char *s21_strstr(const char *str1, const char *str2) {
  char *ret = s21_NULL;
  s21_size_t check = 0;
  int stop = 0;
  s21_size_t len = 0;

  if (str1 != s21_NULL && str2 != s21_NULL) {
    while (str1[len] != '\0' && stop != 1) {
      if (str1[len] == str2[0]) {
        s21_size_t k = len;
        for (int j = 0; str2[j] != '\0'; j++) {
          if (str1[k] == str2[j]) check++;
          k++;
        }
      }
      if (check - 1 == s21_strlen(str2) && str1[len + check - 1] == '\0')
        stop = 1;
      else if (check == s21_strlen(str2) && str1[len + check - 1] != '\0')
        stop = 1;
      len++;
    }
    if (stop == 1) {
      ret = (char *)str1 + len - 1;
    }
  }
  if (s21_strlen(str2) == 0) ret = (char *)str1;

  return ret;
}
