#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (src) {
    if (trim_chars && trim_chars[0]) {
      res = calloc(s21_strlen(src) + 1, sizeof(char));
      int start = 0, end = s21_strlen(src);
      while (firstindex(src, trim_chars, start)) {
        start++;
      }
      if (start != end) {
        while (lastindex(src, trim_chars, end - 1)) {
          end--;
        }
        int k = 0;
        for (int i = start; i < end; i++) {
          res[k] = src[i];
          k++;
        }
      } else {
        res[0] = '\0';
      }
    } else {
      res = s21_trim(src, "\t\n ");
    }
  }
  return res;
}
int firstindex(const char *src, const char *totrim, int start) {
  int res = 0;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[start] == totrim[i]) res = 1;
  }
  return res;
}
int lastindex(const char *src, const char *totrim, int end) {
  int res = 0;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[end] == totrim[i]) res = 1;
  }
  return res;
}
