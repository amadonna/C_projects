#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *rez = NULL;
  if (src != s21_NULL && start_index <= s21_strlen(src)) {
    if (str == s21_NULL)
      rez = (char *)src;
    else {
      s21_size_t len = s21_strlen(src) + s21_strlen(str) + 1;
      rez = calloc(len, sizeof(char));
      int j = 0;
      for (s21_size_t i = 0; i < len - 1; i++) {
        if (i == start_index) {
          for (s21_size_t k = 0; k < s21_strlen(str); k++) {
            rez[j] = str[k];
            j++;
          }
        }
        rez[j] = src[i];
        j++;
      }
      rez[j] = '\0';
    }
  }
  return (void *)rez;
}