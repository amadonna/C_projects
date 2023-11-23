#include "s21_math.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int s21_abs(int x) {
  if (x < 0) x *= -1;
  return x;
}

long double s21_fact(double x) {
  long double rez = 0.0;
  if (x == 0 || x == 1) rez = 1;
  if (x > 1) {
    rez = 1;
    rez = x * s21_fact(x - 1);
  }
  return rez;
}

long double searchCosSin(double x, int n) {
  int stopFlag = 0;
  long double rez = 0.0;
  if (x == 0) {
    if (n == 0) rez = 1;
    if (n == 1) rez = 0;
    stopFlag = 1;
  }
  if (x == s21_NAN || x == s21_INF || x == -s21_INF) {
    rez = s21_NAN;
    stopFlag = 1;
  }

  long double xx = x;

  for (; (xx < -2 * s21_PI || xx > 2 * s21_PI) && !stopFlag;) {
    if (xx > 2 * s21_PI)
      xx -= 2 * s21_PI;
    else if (x < 2 * s21_PI)
      xx += 2 * s21_PI;
  }
  long double prelimRez = 0.0;
  for (int i = 0; i < 100 && !stopFlag; i++) {
    prelimRez += s21_pow(-1, i) * s21_pow((long double)xx, n + 2 * i) /
                 s21_fact(n + 2 * i);
    if (prelimRez == s21_INF || prelimRez == -s21_INF)
      stopFlag = 1;
    else {
      rez = prelimRez;
    }
  }
  return rez;
}

long double s21_sin(double x) { return searchCosSin(x, 1); }

long double s21_cos(double x) { return searchCosSin(x, 0); }

long double s21_tan(double x) {
  long double rez = 0.0;
  if (x == s21_NAN || x == s21_INF || x == -s21_INF)
    rez = s21_NAN;
  else
    rez = s21_sin(x) / s21_cos(x);
  return rez;
}

long double s21_exp(double x) {
  long double rez = 1;
  int stopFlag = 0;
  long double value = 1;

  if (x < -100) {
    rez = 0.0;
    stopFlag = 1;
  }
  for (int i = 1; s21_fabs(value) > s21_EPS && !stopFlag; i++) {
    value *= x / i;
    if (rez > s21_DBL_MAX) {
      stopFlag = 1;
      rez = s21_INF;
    } else
      rez += value;
  }
  return rez;
}

long double s21_pow(double base, double ex) {
  long double rez = 0.0;
  long double dif = 0;
  dif = ex - (long long)ex;
  if (base == s21_NAN || ex == s21_NAN ||
      ((base < 0 && base != -s21_INF) && dif != 0))
    rez = s21_NAN;
  else if ((base == -1 || base == 1) && (ex == -s21_INF || ex == s21_INF))
    rez = 1.0;
  else if (base == 0)
    rez = 0;
  else {
    if (dif == 0) {
      rez = 1;
      if (ex > 0) {
        for (int i = 0; i < (int)ex; i++) rez *= base;
      } else if (ex < 0) {
        ex *= -1;
        for (int i = 0; i < (int)ex; i++) rez /= base;
      }
    } else {
      if (base < 0) {
        base *= -1;
        rez = s21_exp(ex * s21_log(base));
        if (s21_fmod(ex, 2) != 0) rez *= -1;
      } else
        rez = s21_exp(ex * s21_log(base));
    }
  }
  return ex == 0 ? 1 : rez;
}

long double s21_sqrt(double x) {
  long double rez = 0.0;
  if (x == -s21_INF || x < 0 || x == s21_NAN)
    rez = s21_NAN;
  else
    rez = s21_pow(x, 0.5);
  return rez;
}

long double s21_log(double x) {
  long double pow = 0, c_count = 2, result = 0, temp = 0;
  if (x < 0 || x == s21_NAN || x == -s21_INF)
    result = s21_NAN;
  else if (x == 0)
    result = -s21_INF;
  else if (x == s21_INF)
    result = s21_INF;
  else if (x == 1)
    result = 0;
  else {
    while ((x < 1 && x > 0) || (x >= 10)) {
      if (x < 1 && x > 0) {
        x = x * 10;
        pow = pow - 1;
      } else {
        x = x * 0.1;
        pow = pow + 1;
      }
    }
    x = x / 10;
    x--;
    result = x;
    temp = x;
    while (s21_fabs(result) > s21_EPS) {
      result = result * -x * (c_count - 1) / c_count;
      c_count = c_count + 1;
      temp = temp + result;
    }
    result = temp + (pow + 1) * s21_M_LN10;
  }
  return result;
}

long double s21_fabs(double x) {
  if (x == s21_INF || x == -s21_INF) x = s21_INF;
  if (x == s21_NAN || x == -s21_NAN)
    ;
  else if (x < 0)
    x = -1 * x;
  return x;
}

long double s21_fmod(double x, double y) {
  long double rez = 0.0;
  int stopFlag = 0;
  long long int mod = 0;
  if (y == 0 || y == s21_NAN || x == s21_NAN || x == s21_INF || x == -s21_INF) {
    rez = s21_NAN;
    stopFlag = 1;
  } else {
    if ((y == s21_INF || y == -s21_INF) && x != s21_INF) {
      rez = x;
      stopFlag = 1;
    }
  }
  if (!stopFlag) {
    mod = x / y;
    rez = (long double)x - mod * (long double)y;
  }
  return rez;
}

long double s21_atan(double x) {
  long double res = 0;
  long double series = 0;
  long double sum = 0;
  if (x == s21_INF || x == -s21_INF) {
    res = x < 0 ? -s21_PI / 2 : s21_PI / 2;
  } else if (x >= -1 && x <= 1) {
    for (int i = 0; i < 1500; i++) {
      series = (s21_pow(-1, i) * s21_pow(x, 1 + 2 * i)) / (1 + 2 * i);
      res += series;
    }
  } else {
    for (int i = 0; i < 1500; i++) {
      series = (s21_pow(-1, i) * s21_pow(x, -1 - 2 * i)) / (1 + 2 * i);
      sum += series;
    }
    res = ((s21_PI * s21_sqrt(s21_pow(x, 2))) / (2 * x)) - sum;
  }
  if (x == 1 || x == -1) res = x * 0.785398163;
  return res;
}

long double s21_asin(double x) {
  long double res = 0;
  res = s21_atan(x / (s21_sqrt(1 - s21_pow(x, 2))));
  return res;
}

long double s21_acos(double x) {
  long double res = 0;
  if (x >= 0 && x <= 1)
    res = s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
  else
    res = s21_PI + s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
  return res;
}

long double s21_ceil(double x) {
  long double res = (long long)x;
  if (x != x)
    res = s21_NAN;
  else if (x == s21_INF || x == -s21_INF)
    res = x == s21_INF ? s21_INF : -s21_INF;
  else {
    if (x > 0 && (x - res)) res += 1;
    if (res == 0 && x < 0) res = -1 * res;
    if (1 / x == -s21_INF) res = x;
  }
  if (x >= LLONG_MAX) res = x;
  return res;
}

long double s21_floor(double x) {
  long double res = (long long)x;
  if (x != x)
    res = s21_NAN;
  else if (x == s21_INF || x == -s21_INF)
    res = x == s21_INF ? s21_INF : -s21_INF;
  else {
    if (x < 0 && (x - res)) res -= 1;
    if (1 / x == -s21_INF) res = x;
  }
  if (x >= LLONG_MAX) res = x;
  return res;
}
