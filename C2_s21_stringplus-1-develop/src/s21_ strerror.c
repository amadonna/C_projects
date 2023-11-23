#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char res[100] = {0};
  if (errnum < 0 || errnum >= ERRSIZE) {
    s21_sprintf(res, "Unknown error%s%d", s, errnum);
  } else {
    s21_strcpy(res, errors[errnum]);
  }
  return res;
}
