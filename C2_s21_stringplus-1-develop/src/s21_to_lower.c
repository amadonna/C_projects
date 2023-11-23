#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  int length = (int)s21_strlen(str);
  res = (char *)calloc(length + 1, sizeof(char));
  if (res != s21_NULL) {
    for (int i = 0; i < length; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        res[i] = str[i] + ('a' - 'A');
      } else {
        res[i] = str[i];
      }
    }
  }
  return res;
}
