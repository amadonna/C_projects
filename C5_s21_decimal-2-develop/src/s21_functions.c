#include "s21_decimal.h"

int getBit(s21_decimal d, int i) { return !!(d.bits[i / 32] & (1 << i % 32)); }

int setBit(s21_decimal *x, int index, int bit) {
  unsigned int mask = 1u << index % 32;
  if (bit == 1) {
    x->bits[index / 32] |= mask;
  } else {
    x->bits[index / 32] &= ~mask;
  }
  return 0;
}
int long_getBit(long_decimal x, int index) {
  unsigned int mask = 1u << index % 32;
  return !!(x.long_bits[index / 32] & mask);
}

int long_setBit(long_decimal *x, int index, int bit) {
  unsigned int mask = 1u << index % 32;
  if (bit == 1) {
    x->long_bits[index / 32] |= mask;
  } else {
    x->long_bits[index / 32] &= ~mask;
  }
  return 0;
}

int getSign(s21_decimal d) {
  int sign = 1;
  if ((d.bits[3] & (1 << 31)) == 0) sign = 0;
  return sign;
}

int setSign(s21_decimal *x, int sign) {
  if (sign == 0) setBit(x, 127, 0);
  if (sign == 1) setBit(x, 127, 1);
  return sign;
}
int getSign_long(long_decimal d) {
  int sign = 1;
  if ((d.long_bits[6] & (1 << 31)) == 0) sign = 0;
  return sign;
}
int setSign_long(long_decimal *x, int sign) {
  if (sign == 0) long_setBit(x, 223, 0);
  if (sign == 1) long_setBit(x, 223, 1);
  return sign;
}
int getScale_long(long_decimal x) {
  int bit = 0;
  int rez = 0;
  for (int i = 208; i < 213; i++) {
    bit = long_getBit(x, i);
    if (bit) rez += pow(2, (i - 208));
  }
  return rez;
}

int setScale_long(long_decimal *d, int scale) {
  int bit = 0;
  if (scale <= 28 && scale >= 0) {
    for (int i = 4; i >= 0; i--) {
      bit = !!(scale & (1 << i));
      long_setBit(d, 208 + i, bit);
    }
    bit = 1;
  }
  return bit;  // if scale < 0 || > 28 return 0
}

int getScale(s21_decimal x) {
  int bit = 0;
  int rez = 0;
  for (int i = 112; i < 117; i++) {
    bit = getBit(x, i);
    if (bit) rez += pow(2, (i - 112));
  }
  return rez;
}

int setScale(s21_decimal *d, int scale) {
  int bit = 0;
  if (scale <= 28 && scale >= 0) {
    for (int i = 4; i >= 0; i--) {
      bit = !!(scale & (1 << i));
      setBit(d, 112 + i, bit);
    }
    bit = 1;
  }
  return bit;  // if scale < 0 || > 28 return 0
}

int first_bit(s21_decimal dec) {  // определяет индекс первого ненулевого бита
  int first = 0;
  for (int i = 95; i >= 0 && !first; i--) {
    if (getBit(dec, i)) first = i;
  }
  return first;
}

int first_bit_long(
    long_decimal dec) {  // определяет индекс первого ненулевого бита
  int first = 0;
  for (int i = 191; i >= 0 && !first; i--) {
    if (long_getBit(dec, i)) first = i;
  }
  return first;
}

void copy_decimal_long(long_decimal src, long_decimal *dst) {
  dst->long_bits[0] = src.long_bits[0];
  dst->long_bits[1] = src.long_bits[1];
  dst->long_bits[2] = src.long_bits[2];
  dst->long_bits[3] = src.long_bits[3];
  dst->long_bits[4] = src.long_bits[4];
  dst->long_bits[5] = src.long_bits[5];
  dst->long_bits[6] = src.long_bits[6];
}

void shift(s21_decimal *x, int sign) {
  if (sign > 0) {
    x->bits[HIGHE] <<= 1;
    if (getBit(*x, 63)) setBit(x, 64, 1);
    x->bits[MIDLE] <<= 1;
    if (getBit(*x, 31)) setBit(x, 32, 1);
    x->bits[LOW] <<= 1;
  }

  if (sign < 0) {
    x->bits[LOW] >>= 1;
    if (getBit(*x, 32)) setBit(x, 31, 1);
    x->bits[MIDLE] >>= 1;
    if (getBit(*x, 64)) setBit(x, 63, 1);
    x->bits[HIGHE] >>= 1;
  }
}

void long_shift(long_decimal *x, int sign) {
  if (sign > 0) {
    x->long_bits[5] <<= 1;
    if (long_getBit(*x, 159)) long_setBit(x, 160, 1);
    x->long_bits[4] <<= 1;
    if (long_getBit(*x, 127)) long_setBit(x, 128, 1);
    x->long_bits[3] <<= 1;
    if (long_getBit(*x, 95)) long_setBit(x, 96, 1);
    x->long_bits[HIGHE] <<= 1;
    if (long_getBit(*x, 63)) long_setBit(x, 64, 1);
    x->long_bits[MIDLE] <<= 1;
    if (long_getBit(*x, 31)) long_setBit(x, 32, 1);
    x->long_bits[LOW] <<= 1;
  }

  if (sign < 0) {
    x->long_bits[LOW] >>= 1;
    if (long_getBit(*x, 32)) long_setBit(x, 31, 1);
    x->long_bits[MIDLE] >>= 1;
    if (long_getBit(*x, 64)) long_setBit(x, 63, 1);
    x->long_bits[HIGHE] >>= 1;
    x->long_bits[3] >>= 1;
    if (long_getBit(*x, 96)) long_setBit(x, 95, 1);
    x->long_bits[4] >>= 1;
    if (long_getBit(*x, 128)) long_setBit(x, 127, 1);
    x->long_bits[5] >>= 1;
    if (long_getBit(*x, 160)) long_setBit(x, 159, 1);
  }
}
void from_decimal_to_long(s21_decimal dec, long_decimal *dec_long) {
  memset(dec_long, 0, sizeof(*dec_long));
  for (int i = 0; i < 3; i++) {
    dec_long->long_bits[i] = dec.bits[i];
  }
  dec_long->long_bits[6] = dec.bits[3];
}

// сравнение биг децимал без учета знака
int s21_greater_or_equal_long(long_decimal value_1_long,
                              long_decimal value_2_long) {
  int res = 0, stop = 0;
  int bit_val1 = 0;
  int bit_val2 = 0;
  bit_val1 = first_bit_long(value_1_long);
  bit_val2 = first_bit_long(value_2_long);
  if (bit_val1 > bit_val2) {
    res = 1;
  } else if (bit_val2 == bit_val1) {
    for (int i = bit_val2; i >= 0 && !stop; i--) {
      if (long_getBit(value_2_long, i) > long_getBit(value_1_long, i)) {
        stop = 1;
      }  // если стоп, значит value_2 больше
      else if (long_getBit(value_1_long, i) > long_getBit(value_2_long, i)) {
        stop = 2;
      }  //  значит value_1 больше
    }
    res = stop == 2 ? 1 : 0;
    if (stop == 0)  //  значит равны
      res = 1;
  }
  return res;
}

int scale_up(long_decimal *value_smallScale, int bigger_scale,
             int smaller_scale) {
  int is_inf = 0, sign = 0;
  long_decimal tmp = {0};
  long_decimal res = {0};
  sign = getSign_long(*value_smallScale);
  copy_decimal_long(*value_smallScale, &tmp);
  while (smaller_scale < bigger_scale && !is_inf) {
    for (int i = 1; i < 10; i++) {
      is_inf = binary_sum(tmp, *value_smallScale, &res);
      copy_decimal_long(res, &tmp);
    }
    if (!is_inf) {
      copy_decimal_long(res, value_smallScale);
      copy_decimal_long(*value_smallScale, &tmp);
      smaller_scale += 1;
    }
  }
  setScale_long(value_smallScale, smaller_scale);
  setSign_long(value_smallScale, sign);
  return smaller_scale;
}

// ф-я выравнивания степеней
int to_same_scale(long_decimal *value_1, long_decimal *value_2) {
  int scale1 = getScale_long(*value_1);
  int scale2 = getScale_long(*value_2);
  int new_scale = 0;
  if (scale2 > scale1)
    new_scale = scale_up(value_1, scale2, scale1);
  else if (scale1 > scale2)
    new_scale = scale_up(value_2, scale1, scale2);
  return new_scale;
}

int is_zero(long_decimal dec) {
  int zero = 0;
  if (!dec.long_bits[0] && !dec.long_bits[1] && !dec.long_bits[2] &&
      !dec.long_bits[3] && !dec.long_bits[4] && !dec.long_bits[5])
    zero = 1;
  return zero;
}

void sub_from_big(long_decimal value_1_long, long_decimal value_2_long,
                  long_decimal *result_long, int sign_val1, int sign_val2) {
  if (s21_greater_or_equal_long(value_1_long, value_2_long)) {
    binary_sub(value_1_long, value_2_long, result_long);
    if (sign_val1) {
      setSign_long(result_long, sign_val1);
    }
  } else {
    binary_sub(value_2_long, value_1_long, result_long);
    if (sign_val2) setSign_long(result_long, sign_val2);
  }
}

void copy_long_to_dec(long_decimal src, s21_decimal *dst) {
  for (int i = 0; i < 96; i++) {
    setBit(dst, i, long_getBit(src, i));
  }
}

int from_long_to_decimal(long_decimal val1, s21_decimal *result) {
  int ret = 0;
  int scale = 0;
  int sign = 0;
  long_decimal res = {0};
  scale = getScale_long(val1);
  sign = getSign_long(val1);
  if (val1.long_bits[3] != 0 || val1.long_bits[4] != 0 ||
      val1.long_bits[5] != 0) {
    res = div_div(val1);
    scale--;
    while (scale > 0) {
      res = div_div(res);
      scale--;
    }
    if (res.long_bits[3] == 0 && scale >= 0) {
      result->bits[0] = res.long_bits[0];
      result->bits[1] = res.long_bits[1];
      result->bits[2] = res.long_bits[2];
      setScale(result, scale);
    } else
      ret = 1;
  } else {
    result->bits[0] = val1.long_bits[0];
    result->bits[1] = val1.long_bits[1];
    result->bits[2] = val1.long_bits[2];
    setScale(result, scale);
  }
  setSign(result, sign);
  return ret;
}

long_decimal div_div(long_decimal val1) {
  long_decimal temp = {0};
  long_decimal res = {0};
  long_decimal ten = {0};
  long_decimal one = {0};
  one.long_bits[0] = 1;
  ten.long_bits[0] = 10;
  int i = 191;
  int sub = 0;
  while (long_getBit(val1, i) == 0) i--;
  for (; i >= 0; i--) {
    long_shift(&temp, 1);
    long_setBit(&temp, 0, long_getBit(val1, i));
    if (s21_greater_or_equal_long(temp, ten) == 1) {
      sub += 1;
      long_shift(&res, 1);
      long_setBit(&res, 0, 1);
      binary_sub(temp, ten, &temp);
    } else if (sub != 0)
      long_shift(&res, 1);
  }
  if (temp.long_bits[0] >= 5 && long_getBit(res, 191) == 1)
    binary_sum(res, one, &res);
  return res;
}
void init(s21_decimal *dec) {
  dec->bits[0] = 0;
  dec->bits[1] = 0;
  dec->bits[2] = 0;
  dec->bits[3] = 0;
}
s21_decimal divide(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_decimal temp = {0};
  init(result);
  int i = 95;
  while (getBit(value_1, i) == 0) i--;
  int sub = 0;
  for (; i >= 0; i--) {
    shift(&temp, 1);
    setBit(&temp, 0, getBit(value_1, i));
    if (s21_is_greater_or_equal(temp, value_2) == 1) {
      sub += 1;
      shift(result, 1);
      setBit(result, 0, 1);
      s21_sub(temp, value_2, &temp);
    } else if (sub != 0)
      shift(result, 1);
  }
  return temp;
}
void copy_decimal(s21_decimal src, s21_decimal *dst) {
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[3];
}

void bank_round(s21_decimal *res, int i) {
  s21_decimal temp = {0};
  s21_decimal ten = {0};
  s21_decimal one = {0};
  one.bits[0] = 1;
  ten.bits[0] = 10;
  ten.bits[3] = res->bits[3];
  one.bits[3] = res->bits[3];
  if (i >= 5) {
    if (divide(*res, ten, &temp).bits[0] % 2 != 0) s21_add(*res, one, res);
  }
}
