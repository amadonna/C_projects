#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
  int res = 0;
  int sign = 0;
  int float_exp = 0;
  float tmp = 0;
  int scale = 0;
  unions mantissa = {0};
  if (isinf(src) || isnan(src)) {
    res = 1;
  } else {
    if (src < 0) sign = 1;
    float_exp = float_getScale(src);
    tmp = fabs(src);
    scale = 0;
    while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
      tmp *= 10;
      scale++;
    }
    tmp = round(tmp);
    if (scale <= 28 && (float_exp > -94 && float_exp < 96)) {
      while (fmod(tmp, 10) == 0 && scale > 0) {
        scale--;
        tmp /= 10;
      }
      mantissa.fl = tmp;
      float_exp = float_getScale(mantissa.fl);
      setBit(dst, float_exp, 1);
      for (int i = float_exp - 1, j = 22; j >= 0; i--, j--) {
        if ((mantissa.ui & (1 << j)) != 0) {
          setBit(dst, i, 1);
        }
      }
      setSign(dst, sign);
      setScale(dst, scale);
    }
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int resCode = 0;
  double res = 0;
  *dst = 0;
  for (int i = 0; i < 96; i++) {
    if (getBit(src, i)) res += pow(2, i);
  }
  res *= pow(10, (-1 * (getScale(src))));
  *dst = res;
  if (getSign(src)) *dst *= -1;
  return resCode;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  memset(dst, 0, sizeof(*dst));
  if (src < 0) {
    setSign(dst, 1);
    src *= -1;
  }
  dst->bits[LOW] = src;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int resCode = 0;
  if (first_bit(src) > 31)
    resCode = 1;
  else {
    *dst = 0;
    for (int i = 0; i < 96; i++) {
      if (getBit(src, i)) *dst += pow(2, i);
    }
    *dst *= pow(10, (getScale(src) * -1));
    if (getSign(src)) *dst *= -1;
  }
  return resCode;
}

int float_getScale(float value) {
  int res = 0;
  unsigned int fbits = *((unsigned int *)&value);
  int index = 31;
  for (unsigned int mask = 0x80000000; index > 22; mask >>= 1, index--) {
    if (!!(fbits & mask) && (index != 31)) res += pow(2, index - 23);
  }
  return res - 127;
}
