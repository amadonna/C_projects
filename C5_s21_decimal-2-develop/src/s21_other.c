#include "s21_decimal.h"

int s21_negate(s21_decimal value,
               s21_decimal *result) {  // Возвращает результат умножения
                                       // указанного Decimal на -1.
  int ret = 0;
  if (result == NULL)
    ret = 1;
  else {
    if (getSign(value) == 0)
      setSign(&value, 1);
    else if (getSign(value) == 1)
      setSign(&value, 0);
    else
      ret = 1;
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    result->bits[3] = value.bits[3];
  }
  return ret;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  init(result);
  int ret = 0;
  int scale = 0;
  scale = getScale(value);
  s21_decimal ten = {0};
  s21_decimal one = {0};
  one.bits[0] = 1;
  ten.bits[0] = 10;
  one.bits[3] = result->bits[3];
  if (scale > 0) {
    copy_decimal(value, result);
    while (scale > 0) {
      if (divide(*result, ten, result).bits[0] >= 5)
        s21_add(*result, one, result);
      scale--;
    }
    setSign(result, getSign(value));
  } else if (scale == 0)
    copy_decimal(value, result);
  else
    ret = 1;
  return ret;
}

int s21_truncate(
    s21_decimal value,
    s21_decimal
        *result) {  // Возвращает целые цифры указанного Decimal числа; любые
                    // дробные цифры отбрасываются, включая конечные нули.
  init(result);
  int ret = 0;
  int scale = getScale(value);
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  if (scale > 0) {
    copy_decimal(value, result);
    while (scale > 0) {
      divide(*result, ten, result);
      scale--;
    }
    setSign(result, getSign(value));
    setScale(result, 0);
  } else if (scale == 0) {
    copy_decimal(value, result);
    setScale(result, scale);
  } else
    ret = 1;
  return ret;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one = {0};
  init(result);
  one.bits[0] = 1;
  int ret = 0;
  if (s21_truncate(value, result) == 0) {
    one.bits[3] = result->bits[3];
    if (getSign(*result) == 1 && getScale(value) != 0)
      s21_add(*result, one, result);
  } else
    ret = 1;
  return ret;
}
