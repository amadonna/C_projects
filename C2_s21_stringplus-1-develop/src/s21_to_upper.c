#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  int length = 0;
  length = (int)s21_strlen(str);
  res = (char *)calloc(length + 1, sizeof(char));
  if (res != s21_NULL) {
    for (int i = 0; i < length; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        res[i] = str[i] - (char)('a' - 'A');
      } else {
        res[i] = str[i];
      }
    }
  }
  return res;
}
