#include "s21_decimal.h"

// binary_sum - алгоритм суммирования положительных целых чисел в двоичной
// системе
int binary_sum(long_decimal value_1, long_decimal value_2, long_decimal *res) {
  memset(res, 0, sizeof(*res));
  int tmp = 0;
  for (int i = 0; i < 192; i++) {
    if (long_getBit(value_1, i) && long_getBit(value_2, i) && tmp)
      long_setBit(res, i, 1);
    else if (long_getBit(value_1, i) && long_getBit(value_2, i) && !tmp)
      tmp = 1;
    else if ((long_getBit(value_1, i) + long_getBit(value_2, i)) == 1 && !tmp)
      long_setBit(res, i, 1);
    else if (!long_getBit(value_1, i) && !long_getBit(value_2, i) && tmp) {
      long_setBit(res, i, 1);
      tmp = 0;
    }
  }
  return tmp;
}

// binary_sub - алгоритм вычитания положительных целых чисел в двоичной
// системе
void binary_sub(long_decimal value_1, long_decimal value_2, long_decimal *res) {
  long_decimal val2_dop_code = {0};
  memset(res, 0, sizeof(*res));
  int first_Bit = 0;
  first_Bit = first_bit_long(value_1);
  dop_Code(value_2, &val2_dop_code, first_Bit);
  binary_sum(value_1, val2_dop_code, res);
  if (long_getBit(*res, first_Bit + 1)) long_setBit(res, first_Bit + 1, 0);
}

// dop_Code - перевод в дополнительный код (для вычитания)
void dop_Code(long_decimal value, long_decimal *dop_code, int first_index) {
  for (int i = first_index; i >= 0; i--) {
    long_setBit(dop_code, i, long_getBit(value, i) ? 0 : 1);
  }
  dop_code->long_bits[0] += 1;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_code = 0, sign_val1 = 0, sign_val2 = 0, res_scale = 0;
  long_decimal value_1_long = {0};
  long_decimal value_2_long = {0};
  long_decimal result_long = {0};
  sign_val1 = getSign(value_1);
  sign_val2 = getSign(value_2);
  memset(result, 0, sizeof(*result));
  from_decimal_to_long(value_1, &value_1_long);
  from_decimal_to_long(value_2, &value_2_long);
  if (is_zero(value_1_long))
    copy_decimal_long(value_2_long, &result_long);
  else if (is_zero(value_2_long))
    copy_decimal_long(value_1_long, &result_long);
  else {
    if (getScale_long(value_1_long) != getScale_long(value_2_long))
      res_scale = to_same_scale(&value_1_long, &value_2_long);
    else
      res_scale = getScale_long(value_1_long);
    if (sign_val1 == sign_val2) {  // оба знака одинаковы
      binary_sum(value_1_long, value_2_long, &result_long);
      if (sign_val1) {
        setSign_long(&result_long, sign_val1);
      }
    } else {  // знаки разные - вычитаем из большего
      sub_from_big(value_1_long, value_2_long, &result_long, sign_val1,
                   sign_val2);
    }
    setScale_long(&result_long, res_scale);
  }
  if (is_zero(result_long)) setSign_long(&result_long, 0);
  res_code =
      from_long_to_decimal(result_long, result);  // если переполнение - код 1
  if (res_code && getSign(*result))
    res_code = 2;  // если переполнение с минусом - код 2
  return res_code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_code = 0, res_scale = 0, sign_val1 = 0, sign_val2 = 0;
  long_decimal value_1_long = {0};
  long_decimal value_2_long = {0};
  long_decimal result_long = {0};
  sign_val1 = getSign(value_1);
  sign_val2 = getSign(value_2);
  memset(result, 0, sizeof(*result));
  from_decimal_to_long(value_1, &value_1_long);
  from_decimal_to_long(value_2, &value_2_long);
  if (is_zero(value_1_long)) {
    copy_decimal_long(value_2_long, &result_long);
    setSign_long(&result_long, getSign_long(value_2_long) == 1 ? 0 : 1);
  } else if (is_zero(value_2_long)) {
    copy_decimal_long(value_1_long, &result_long);
  } else {
    if (getScale_long(value_1_long) != getScale_long(value_2_long))
      res_scale = to_same_scale(&value_1_long, &value_2_long);
    else
      res_scale = getScale_long(value_1_long);
    if (sign_val1 == sign_val2) {  // оба знака одинаковы - вычитаем из большего
      sub_from_big(value_1_long, value_2_long, &result_long, sign_val1,
                   sign_val2);
      if (s21_greater_or_equal_long(value_2_long, value_1_long))
        setSign_long(&result_long, sign_val2 == 1 ? 0 : 1);
    } else {  // знаки разные -складываем
      binary_sum(value_1_long, value_2_long, &result_long);
      if (sign_val1) setSign_long(&result_long, sign_val1);
    }
    setScale_long(&result_long, res_scale);
  }
  if (is_zero(result_long)) setSign_long(&result_long, 0);
  res_code = from_long_to_decimal(result_long, result);
  if (res_code && getSign(*result))
    res_code = 2;  // если переполнение с минусом - код 2
  return res_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *res) {
  int res_code = 0, resScale = 0, resSign = 1;
  memset(res, 0, sizeof(*res));
  float a = 0, b = 0;
  s21_from_decimal_to_float(value_1, &a);
  s21_from_decimal_to_float(value_2, &b);
  long_decimal long_res = {0};
  long_decimal val_1 = {0};
  long_decimal val_2 = {0};
  double summa = 0;
  if (a != 0 && b != 0) {
    if (getSign(value_1)) {
      if (getSign(value_2)) {
        resSign = 1;
        a *= -1;
        b *= -1;
      }
      if (!getSign(value_2)) {
        resSign = -1;
        a *= -1;
      }
    } else {
      if (getSign(value_2)) {
        resSign = -1;
        b *= -1;
      }
    }
    resScale = getScale(value_1) + getScale(value_2);

    if (a == 1) {
      copy_decimal(value_2, res);
      resSign == 1 ? setSign(res, 0) : setSign(res, 1);
    } else if (b == 1) {
      copy_decimal(value_1, res);
      resSign == 1 ? setSign(res, 0) : setSign(res, 1);
    } else {
      for (int i = 0; i < 3; i++) {
        val_1.long_bits[i] = value_1.bits[i];
        val_2.long_bits[i] = value_2.bits[i];
      }
      for (int i = 0; i < 192; i++) {
        if (long_getBit(val_2, i))
          res_code = binary_sum(long_res, val_1, &long_res);
        long_shift(&val_1, 1);
      }
      setScale_long(&long_res, resScale);
      summa = 0;
      for (int i = 0; i < 192; i++) {
        if (long_getBit(long_res, i)) summa += pow(2, i);
      }
      summa *= pow(10, (-1 * resScale)) * resSign;
      if (summa >= MAX_VALUE) res_code = 1;
      if (summa <= MIN_VALUE) res_code = 2;
      if (!res_code) {
        resSign == 1 ? setSign(res, 0) : setSign(res, 1);
        if (!resScale)
          copy_long_to_dec(long_res, res);
        else
          from_long_to_decimal(long_res, res);
      }
    }
  }
  return res_code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  init(result);
  s21_decimal temp = {0};
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  int ret = 0;
  int scale = 0;
  int sign = 0;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)
    ret = 3;
  else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0)
    memset(result, 0, sizeof(*result));
  else if (s21_is_equal(value_1, value_2) == 1)
    result->bits[0] = 1;
  else {
    scale = getScale(value_1) - getScale(value_2);
    setScale(&value_1, 0);
    setScale(&value_2, 0);
    sign = getSign(value_1) - getSign(value_2);
    if (sign == -1) sign = 1;
    setSign(&value_1, 0);
    setSign(&value_2, 0);
    if (sign != 0) sign = 1;
    temp = divide(value_1, value_2, result);
    div_mod(&temp, result, value_2, &scale, &ret);
    bank_round(result, temp.bits[0]);
    if (scale < 0 && ret == 0) {
      while (scale < 0) {
        s21_mul(*result, ten, result);
        scale++;
      }
      if (result->bits[0] == 0 && result->bits[1] == 0 &&
          result->bits[2] == 0) {
        ret = sign == 0 ? 1 : 2;
        scale = 0;
        sign = 0;
      }
    }
    setScale(result, scale);
    setSign(result, sign);
  }
  return ret;
}

void div_mod(s21_decimal *temp, s21_decimal *result, s21_decimal value_2,
             int *scale, int *ret) {
  s21_decimal res_temp = {0};
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  while ((temp->bits[0] != 0 || temp->bits[1] != 0 || temp->bits[2] != 0) &&
         first_bit(*result) < 91 && *scale < 28) {
    init(&res_temp);
    while (s21_is_less(*temp, value_2) == 1 && first_bit(*temp) < 93) {
      s21_mul(*temp, ten, temp);
      s21_mul(*result, ten, result);
      *scale += 1;
    }
    if (*scale > 28) {
      *ret = 2;
      init(result);
    } else {
      *temp = divide(*temp, value_2, &res_temp);
      res_temp.bits[3] = result->bits[3];
      s21_add(res_temp, *result, result);
    }
  }
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  int sign = 0;
  s21_decimal res_temp = {0};
  s21_decimal mul_temp = {0};
  init(result);
  sign = getSign(value_1);
  setSign(&value_1, 0);
  setSign(&value_2, 0);
  ret = s21_div(value_1, value_2, &res_temp);
  if (ret == 0) {
    s21_truncate(res_temp, &res_temp);
    s21_mul(value_2, res_temp, &mul_temp);
    s21_sub(value_1, mul_temp, result);
    setSign(result, sign);
  }
  return ret;
}
