#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0, stop = 0;
  long_decimal value_1_long = {0};
  long_decimal value_2_long = {0};
  from_decimal_to_long(value_1, &value_1_long);
  from_decimal_to_long(value_2, &value_2_long);
  if (is_zero(value_1_long) && is_zero(value_2_long))
    res = 1;
  else if (value_1.bits[3] == value_2.bits[3]) {
    if (value_1.bits[0] == value_2.bits[0] &&
        value_1.bits[1] == value_2.bits[1] &&
        value_1.bits[2] == value_2.bits[2])
      res = 1;
  } else if (getSign(value_1) == getSign(value_2)) {
    to_same_scale(&value_1_long,
                  &value_2_long);  // сравнение после приведения скейлов
    for (int i = 191; i >= 0 && !stop; i--) {
      if (long_getBit(value_1_long, i) != long_getBit(value_2_long, i))
        stop = 1;
    }
    res = stop ? 0 : 1;
  }
  return res;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 0, stop = 0;
  int bit_val1 = 0;
  int bit_val2 = 0;
  long_decimal value_1_long = {0};
  long_decimal value_2_long = {0};
  from_decimal_to_long(value_1, &value_1_long);
  from_decimal_to_long(value_2, &value_2_long);
  if (!s21_is_equal(value_1, value_2)) {
    if (is_zero(value_1_long)) setSign_long(&value_1_long, 0);
    if (is_zero(value_2_long)) setSign_long(&value_2_long, 0);
    if (getSign(value_1) && !getSign(value_2))
      res = 1;
    else if (getSign(value_1) == getSign(value_2)) {
      to_same_scale(&value_1_long, &value_2_long);
      bit_val1 = first_bit_long(value_1_long);
      bit_val2 = first_bit_long(value_2_long);
      if (bit_val2 > bit_val1) {
        res = 1;
      } else if (bit_val2 == bit_val1) {
        for (int i = bit_val2; i >= 0 && !stop; i--) {
          if (long_getBit(value_2_long, i) > long_getBit(value_1_long, i))
            stop = 1;  // если стоп, значит value_2 больше
          else if (long_getBit(value_1_long, i) > long_getBit(value_2_long, i))
            stop = 2;  //  значит value_1 больше
        }
        res = stop == 1 ? 1 : 0;
      }
      res = getSign_long(value_1_long) ? !res : res;
    }
  }
  return res;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  if (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2)) res = 1;
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  if (!s21_is_less(value_1, value_2) && !s21_is_equal(value_1, value_2))
    res = 1;
  return res;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  if (!s21_is_less(value_1, value_2)) res = 1;
  return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  if (!s21_is_equal(value_1, value_2)) res = 1;
  return res;
}
