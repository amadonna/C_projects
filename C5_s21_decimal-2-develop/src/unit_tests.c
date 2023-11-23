#include <check.h>

#define U_MAX_INT 4294967295          // 0b11111111111111111111111111111111
#define MAX_INT 2147483647            // 0b01111111111111111111111111111111
#define EXPONENT_MINUS_1 2147549184   // 0b10000000000000010000000000000000
#define EXPONENT_PLUS_1 65536         // 0b00000000000000010000000000000000
#define EXPONENT_PLUS_3 196608        // 0b00000000000000110000000000000000
#define EXPONENT_MINUS_3 2147680256   // 0b10000000000000110000000000000000
#define EXPONENT_MINUS_28 2149318656  // 0b10000000000111000000000000000000
#define EXPONENT_PLUS_28 1835008      // 0b00000000000111000000000000000000
#define MINUS 2147483648              // 0b10000000000000000000000000000000

#include "s21_decimal.h"

START_TEST(mul_test) {
  int num1 = -10;
  int num2 = -10;
  int mul_res = 100;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res);
  ck_assert_int_eq(res, mul_res);

  num1 = 10;
  num2 = 20;
  mul_res = 200;
  s21_decimal a_1 = {0};
  s21_decimal b_1 = {0};
  s21_from_int_to_decimal(num1, &a_1);
  s21_from_int_to_decimal(num2, &b_1);
  s21_decimal res_dec_1 = {0};
  res = 0;
  s21_mul(a_1, b_1, &res_dec_1);
  s21_from_decimal_to_int(res_dec_1, &res);
  ck_assert_int_eq(res, mul_res);

  num1 = -10;
  num2 = 20;
  mul_res = -200;
  s21_decimal a_2 = {0};
  s21_decimal b_2 = {0};
  s21_from_int_to_decimal(num1, &a_2);
  s21_from_int_to_decimal(num2, &b_2);
  s21_decimal res_dec_2 = {0};
  res = 0;
  s21_mul(a_2, b_2, &res_dec_2);
  s21_from_decimal_to_int(res_dec_2, &res);
  ck_assert_int_eq(res, mul_res);

  num1 = 9403;
  num2 = 202;
  mul_res = num1 * num2;
  s21_decimal a_3 = {0};
  s21_decimal b_3 = {0};
  s21_from_int_to_decimal(num1, &a_3);
  s21_from_int_to_decimal(num2, &b_3);
  s21_decimal res_dec_3 = {0};
  res = 0;
  s21_mul(a_3, b_3, &res_dec_3);
  s21_from_decimal_to_int(res_dec_3, &res);
  ck_assert_int_eq(res, mul_res);

  num1 = -32768;
  num2 = 2;
  mul_res = -65536;
  s21_decimal a_4 = {0};
  s21_decimal b_4 = {0};
  s21_from_int_to_decimal(num1, &a_4);
  s21_from_int_to_decimal(num2, &b_4);
  s21_decimal res_dec_4 = {0};
  res = 0;
  s21_mul(a_4, b_4, &res_dec_4);
  s21_from_decimal_to_int(res_dec_4, &res);
  ck_assert_int_eq(res, mul_res);

  num1 = -32768;
  num2 = 32768;
  mul_res = num1 * num2;
  s21_decimal a_5 = {0};
  s21_decimal b_5 = {0};
  s21_from_int_to_decimal(num1, &a_5);
  s21_from_int_to_decimal(num2, &b_5);
  s21_decimal res_dec_5 = {0};
  res = 0;
  s21_mul(a_5, b_5, &res_dec_5);
  s21_from_decimal_to_int(res_dec_5, &res);
  ck_assert_int_eq(res, mul_res);

  float fnum1 = 9403.0e2;
  num2 = 202;
  float fres = fnum1 * num2;
  s21_decimal a_6 = {0};
  s21_decimal b_6 = {0};
  s21_from_float_to_decimal(fnum1, &a_6);
  s21_from_int_to_decimal(num2, &b_6);
  s21_decimal res_dec_6 = {0};
  float res_float = 0;
  s21_mul(a_6, b_6, &res_dec_6);
  s21_from_decimal_to_float(res_dec_6, &res_float);
  ck_assert_float_eq(res_float, fres);

  fnum1 = 9403.0e2;
  float fnum2 = 9403.0e2;
  fres = 884164090000;
  s21_decimal a_7 = {0};
  s21_decimal b_7 = {0};
  s21_from_float_to_decimal(fnum1, &a_7);
  s21_from_float_to_decimal(fnum2, &b_7);
  s21_decimal res_dec_7 = {0};
  res_float = 0;
  s21_mul(a_7, b_7, &res_dec_7);
  s21_from_decimal_to_float(res_dec_7, &res_float);
  ck_assert_float_eq(res_float, fres);

  s21_decimal a_8 = {{4, 0, 0, 0}};
  s21_decimal b_8 = {{10, 0, 0, 0}};

  s21_decimal res_dec_8 = {0};
  s21_mul(a_8, b_8, &res_dec_8);

  res = 0;
  s21_from_decimal_to_int(res_dec_8, &res);
  ck_assert_int_eq(res, 40);

  s21_decimal a_9;
  a_9.bits[0] = 0b01110000000000000000000000000000;
  a_9.bits[1] = 0b10110011000000110001000010100111;
  a_9.bits[2] = 0b11100010001011101010010010010011;
  a_9.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal b_9;
  b_9.bits[0] = 0b00000000000000000000000000000001;
  b_9.bits[1] = 0b10000000000000100000000000000000;
  b_9.bits[2] = 0b00000000000000000000000000000000;
  b_9.bits[3] = 0b00000000000000000000000000000000;

  s21_decimal res_dec_9 = {0};
  int error = s21_mul(a_9, b_9, &res_dec_9);
  ck_assert_int_eq(error, 1);

  s21_decimal a_10;
  a_10.bits[0] = 0b01110000000000000000000000000000;
  a_10.bits[1] = 0b10110011000000110001000010100111;
  a_10.bits[2] = 0b11100010001011101010010010010011;
  a_10.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal b_10;
  b_10.bits[0] = 0b00000000000000000000000000000001;
  b_10.bits[1] = 0b10000000000000100000000000000000;
  b_10.bits[2] = 0b00000000000000000000000000000000;
  b_10.bits[3] = MINUS;

  s21_decimal rec_dec_10 = {0};
  error = s21_mul(a_10, b_10, &rec_dec_10);
  ck_assert_int_eq(error, 2);

  s21_decimal a_11 = {{100, 0, 0, 0}};  // 100
  s21_decimal b_11 = {0};
  float fl = 9999.99;
  s21_from_float_to_decimal(fl, &b_11);
  s21_decimal res_dec_11 = {0};
  s21_mul(a_11, b_11, &res_dec_11);
  s21_from_decimal_to_float(res_dec_11, &fl);
  ck_assert_float_eq_tol(fl, 999999, 1e+6);

  s21_decimal a_12 = {{U_MAX_INT - 1, U_MAX_INT - 1, U_MAX_INT - 1, 0}};
  s21_decimal b_12 = {{2, 0, 0, 0}};

  s21_decimal res_dec_12;
  int resCode = s21_mul(a_12, b_12, &res_dec_12);

  ck_assert_int_eq(resCode, 1);

  s21_decimal a_13 = {{123456789, 0, 0, 0}};
  setScale(&a_13, 10);
  s21_decimal b_13 = {{123456789, 0, 0, 0}};
  setScale(&b_13, 10);

  s21_decimal res_dec_13 = {0};
  s21_mul(a_13, b_13, &res_dec_13);
  fl = 0;
  s21_from_decimal_to_float(res_dec_13, &fl);
  ck_assert_float_eq(fl, 0.00015241578512359410524368286132812);

  s21_decimal a_14 = {{U_MAX_INT - 1, U_MAX_INT - 1, U_MAX_INT - 1, 0}};
  setSign(&a_14, 1);
  s21_decimal b_14 = {{2, 0, 0, 0}};

  s21_decimal res_dec_14;
  resCode = s21_mul(a_14, b_14, &res_dec_14);

  ck_assert_int_eq(resCode, 2);

  s21_decimal a_15 = {{125, 1, 5, 0}};
  s21_decimal b_15 = {{1, 0, 0, 0}};
  s21_decimal res_dec_15 = {0};
  s21_mul(a_15, b_15, &res_dec_15);
  res = s21_is_equal(a_15, res_dec_15);
  ck_assert_int_eq(1, res);

  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_1 = {0};
  s21_decimal res_dec_16 = {0};
  int return_value = s21_mul(value_2, value_1, &res_dec_16), result_int = 0;
  ck_assert_int_eq(return_value, 0);
  s21_from_decimal_to_int(res_dec_16, &result_int);
  ck_assert_int_eq(result_int, 0);

  s21_decimal value_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_4 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  return_value = s21_mul(value_3, value_4, &result);
  ck_assert_int_eq(return_value, 1);

  s21_decimal value_5 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_6 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result_2 = {0};
  return_value = s21_mul(value_5, value_6, &result_2);
  ck_assert_int_eq(return_value, 2);

  s21_decimal src1, src2, origin, res_dec_17;
  int value_type_result, value_type_origin;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &res_dec_17);
  value_type_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], res_dec_17.bits[3]);
  ck_assert_int_eq(origin.bits[2], res_dec_17.bits[2]);
  ck_assert_int_eq(origin.bits[1], res_dec_17.bits[1]);
  ck_assert_int_eq(origin.bits[0], res_dec_17.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);

  s21_decimal src3, src4, origin_2, res_dec_18;
  int value_type_result2, value_type_origin2;
  src3.bits[0] = 0b00000000000000000000000000000011;
  src3.bits[1] = 0b00000000000000000000000000000000;
  src3.bits[2] = 0b00000000000000000000000000000000;
  src3.bits[3] = 0b00000000000000000000000000000000;
  src4.bits[0] = 0b00000000000000000000000000000010;
  src4.bits[1] = 0b00000000000000000000000000000000;
  src4.bits[2] = 0b00000000000000000000000000000000;
  src4.bits[3] = 0b00000000000000000000000000000000;
  value_type_result2 = s21_mul(src3, src4, &res_dec_18);
  value_type_origin2 = 0;
  origin_2.bits[0] = 0b00000000000000000000000000000110;
  origin_2.bits[1] = 0b00000000000000000000000000000000;
  origin_2.bits[2] = 0b00000000000000000000000000000000;
  origin_2.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin_2.bits[3], res_dec_18.bits[3]);
  ck_assert_int_eq(origin_2.bits[2], res_dec_18.bits[2]);
  ck_assert_int_eq(origin_2.bits[1], res_dec_18.bits[1]);
  ck_assert_int_eq(origin_2.bits[0], res_dec_18.bits[0]);
  ck_assert_int_eq(value_type_result2, value_type_origin2);

  s21_decimal src5, src6, origin3, res_dec_19;
  int value_type_result3, value_type_origin3;
  src5.bits[0] = 0b00000000000000000000000000000000;
  src5.bits[1] = 0b00000000000000000000000000000000;
  src5.bits[2] = 0b00000000000000000000000000000000;
  src5.bits[3] = 0b00000000000000000000000000000000;
  src6.bits[0] = 0b00000000000000000000000000000011;
  src6.bits[1] = 0b00000000000000000000000000000000;
  src6.bits[2] = 0b00000000000000000000000000000000;
  src6.bits[3] = 0b00000000000000000000000000000000;
  value_type_result3 = s21_mul(src5, src6, &res_dec_19);
  value_type_origin3 = 0;
  origin3.bits[0] = 0b00000000000000000000000000000000;
  origin3.bits[1] = 0b00000000000000000000000000000000;
  origin3.bits[2] = 0b00000000000000000000000000000000;
  origin3.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin3.bits[3], res_dec_19.bits[3]);
  ck_assert_int_eq(origin3.bits[2], res_dec_19.bits[2]);
  ck_assert_int_eq(origin3.bits[1], res_dec_19.bits[1]);
  ck_assert_int_eq(origin3.bits[0], res_dec_19.bits[0]);
  ck_assert_int_eq(value_type_result3, value_type_origin3);

  s21_decimal src7, src8, origin8, result8;
  int value_type_result8, value_type_origin8;
  src7.bits[0] = 0b00000000000000000000000000000010;
  src7.bits[1] = 0b00000000000000000000000000000000;
  src7.bits[2] = 0b00000000000000000000000000000000;
  src7.bits[3] = 0b00000000000000000000000000000000;
  src8.bits[0] = 0b00000000000000000000000000000000;
  src8.bits[1] = 0b00000000000000000000000000000000;
  src8.bits[2] = 0b00000000000000000000000000000000;
  src8.bits[3] = 0b00000000000000000000000000000000;
  value_type_result8 = s21_mul(src7, src8, &result8);
  value_type_origin8 = 0;
  origin8.bits[0] = 0b00000000000000000000000000000000;
  origin8.bits[1] = 0b00000000000000000000000000000000;
  origin8.bits[2] = 0b00000000000000000000000000000000;
  origin8.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin8.bits[3], result8.bits[3]);
  ck_assert_int_eq(origin8.bits[2], result8.bits[2]);
  ck_assert_int_eq(origin8.bits[1], result8.bits[1]);
  ck_assert_int_eq(origin8.bits[0], result8.bits[0]);
  ck_assert_int_eq(value_type_result8, value_type_origin8);

  s21_decimal src9, src10, origin9, result9;
  int value_type_result9, value_type_origin9;
  src9.bits[0] = 0b00000000000000000000000000000000;
  src9.bits[1] = 0b00000000000000000000000000000000;
  src9.bits[2] = 0b00000000000000000000000000000000;
  src9.bits[3] = 0b10000000000000010000000000000000;
  src10.bits[0] = 0b00000000000000000000000000000011;
  src10.bits[1] = 0b00000000000000000000000000000000;
  src10.bits[2] = 0b00000000000000000000000000000000;
  src10.bits[3] = 0b00000000000000000000000000000000;
  value_type_result9 = s21_mul(src9, src10, &result9);
  value_type_origin9 = 0;
  origin9.bits[0] = 0b00000000000000000000000000000000;
  origin9.bits[1] = 0b00000000000000000000000000000000;
  origin9.bits[2] = 0b00000000000000000000000000000000;
  origin9.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin9.bits[3], result9.bits[3]);
  ck_assert_int_eq(origin9.bits[2], result9.bits[2]);
  ck_assert_int_eq(origin9.bits[1], result9.bits[1]);
  ck_assert_int_eq(origin9.bits[0], result9.bits[0]);
  ck_assert_int_eq(value_type_result9, value_type_origin9);

  s21_decimal src11, src12, origin10, result10;
  int value_type_result10, value_type_origin10;
  // src1 = 6521;
  // src2 = 74121;
  src11.bits[0] = 0b00000000000000000001100101111001;
  src11.bits[1] = 0b00000000000000000000000000000000;
  src11.bits[2] = 0b00000000000000000000000000000000;
  src11.bits[3] = 0b00000000000000000000000000000000;
  src12.bits[0] = 0b00000000000000010010000110001001;
  src12.bits[1] = 0b00000000000000000000000000000000;
  src12.bits[2] = 0b00000000000000000000000000000000;
  src12.bits[3] = 0b00000000000000000000000000000000;
  value_type_result10 = s21_mul(src11, src12, &result10);
  value_type_origin10 = 0;
  origin10.bits[0] = 0b00011100110011110011101011000001;
  origin10.bits[1] = 0b00000000000000000000000000000000;
  origin10.bits[2] = 0b00000000000000000000000000000000;
  origin10.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin10.bits[3], result10.bits[3]);
  ck_assert_int_eq(origin10.bits[2], result10.bits[2]);
  ck_assert_int_eq(origin10.bits[1], result10.bits[1]);
  ck_assert_int_eq(origin10.bits[0], result10.bits[0]);
  ck_assert_int_eq(value_type_result10, value_type_origin10);

  s21_decimal src13, src14, origin11, result11;
  int value_type_result11, value_type_origin11;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;
  src13.bits[0] = 0b11111111111111111111111111110110;
  src13.bits[1] = 0b11111111111111111111111111111111;
  src13.bits[2] = 0b00000000000000000000000000001001;
  src13.bits[3] = 0b00000000000000010000000000000000;
  src14.bits[0] = 0b00111001100010111010010101100010;
  src14.bits[1] = 0b00000000000000000000000000000000;
  src14.bits[2] = 0b00000000000000000000000000000000;
  src14.bits[3] = 0b00000000000000000000000000000000;
  value_type_result11 = s21_mul(src13, src14, &result11);
  value_type_origin11 = 0;
  origin11.bits[0] = 0b11000110011101000101101010011110;
  origin11.bits[1] = 0b11111111111111111111111111111111;
  origin11.bits[2] = 0b00111001100010111010010101100001;
  origin11.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin11.bits[3], result11.bits[3]);
  ck_assert_int_eq(origin11.bits[2], result11.bits[2]);
  ck_assert_int_eq(origin11.bits[1], result11.bits[1]);
  ck_assert_int_eq(origin11.bits[0], result11.bits[0]);
  ck_assert_int_eq(value_type_result11, value_type_origin11);
}
END_TEST

START_TEST(convert_test) {
  s21_decimal x = {0};
  x.bits[LOW] = MAX_INT;
  int value = 2147483647;
  int value_2 = 0;
  s21_from_decimal_to_int(x, &value_2);
  ck_assert_int_eq(value, value_2);

  s21_decimal y = {0};
  s21_from_int_to_decimal(value, &y);
  int res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  x.bits[SCALE] = MINUS;
  value = -2147483647;
  value_2 = 0;
  s21_from_decimal_to_int(x, &value_2);
  ck_assert_int_eq(value, value_2);

  s21_from_int_to_decimal(value, &y);
  res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  x.bits[LOW] = 9;
  x.bits[SCALE] = EXPONENT_PLUS_1;
  s21_from_decimal_to_int(x, &value);
  ck_assert_int_eq(0, value);

  float fl = 234.678;
  x.bits[LOW] = 234678;
  x.bits[SCALE] = EXPONENT_PLUS_3;
  float fl_2 = 0;
  s21_from_decimal_to_float(x, &fl_2);
  ck_assert_float_eq(fl, fl_2);

  s21_from_float_to_decimal(fl, &y);
  res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  fl = 0.000000456;
  s21_from_float_to_decimal(fl, &x);
  s21_from_decimal_to_float(x, &fl_2);
  ck_assert_float_eq_tol(fl, fl_2, 1e28);

  s21_from_float_to_decimal(fl_2, &y);
  res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  fl = -0.000000456;
  s21_from_float_to_decimal(fl, &x);
  s21_from_decimal_to_float(x, &fl_2);
  ck_assert_float_eq_tol(fl, fl_2, 1e28);

  s21_from_float_to_decimal(fl_2, &y);
  res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  fl = 8589934591;
  s21_from_float_to_decimal(fl, &x);
  s21_from_decimal_to_float(x, &fl_2);
  ck_assert_float_eq(fl, fl_2);

  s21_from_float_to_decimal(fl_2, &y);
  res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  fl = -9589934591.512;
  s21_from_float_to_decimal(fl, &x);
  s21_from_decimal_to_float(x, &fl_2);
  ck_assert_float_eq(fl, fl_2);

  s21_from_float_to_decimal(fl_2, &y);
  res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  fl = -1.1068046444226E+20;
  s21_from_float_to_decimal(fl, &x);
  s21_from_decimal_to_float(x, &fl_2);
  ck_assert_float_eq(fl, fl_2);

  s21_from_float_to_decimal(fl_2, &y);
  res = s21_is_equal(x, y);
  ck_assert_int_eq(1, res);

  fl = INFINITY;
  res = s21_from_float_to_decimal(fl, &x);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(add_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale= 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal result = {0};
  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;
  float res_float = 0.0;

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_add(tmp1, ten, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, random_pos_int + 10);

  memset(&result, 0, sizeof(result));
  memset(&tmp1, 0, sizeof(tmp1));
  s21_add(zero, negative_zero, &result);
  res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_add(zero, tmp1, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, random_pos_int);

  memset(&result, 0, sizeof(result));
  memset(&tmp1, 0, sizeof(tmp1));
  res = 0;
  s21_from_int_to_decimal(random_neg_int, &tmp1);
  s21_add(zero, tmp1, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, random_neg_int);

  memset(&result, 0, sizeof(result));
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  res = 0;
  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  s21_add(tmp1, tmp2, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, random_pos_int + random_neg_int);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_add(one, other_ten, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 11);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_add(ten, other_ten, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 20);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_add(ten, other_ten_neg, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  memset(&result, 0, sizeof(result));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  s21_add(tmp1, tmp2, &result);
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq_tol(res_float, random_pos_float + random_pos_float2,
                         1e-02);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  memset(&result, 0, sizeof(result));
  s21_from_float_to_decimal(random_neg_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float2, &tmp2);
  s21_add(tmp1, tmp2, &result);
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq_tol(res_float, random_neg_float + random_neg_float2,
                         1e-02);

  memset(&result, 0, sizeof(result));
  s21_add(big_num_positive, zero, &result);
  ck_assert_int_eq(result.bits[0], big_num_positive.bits[0]);
  ck_assert_int_eq(result.bits[1], big_num_positive.bits[1]);
  ck_assert_int_eq(result.bits[2], big_num_positive.bits[2]);
  ck_assert_int_eq(result.bits[3], big_num_positive.bits[3]);

  memset(&result, 0, sizeof(result));
  s21_add(big_num_positive, big_num_negative, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);

  memset(&result, 0, sizeof(result));
  s21_add(long_num_positive, long_num_negative, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);

  memset(&result, 0, sizeof(result));
  memset(&tmp1, 0, sizeof(tmp1));
  ck_assert_int_eq(s21_add(long_num_positive, big_num_negative, &result), 0);

  memset(&result, 0, sizeof(result));
  res = s21_add(big_num_negative, other_ten_neg, &result);
  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(sub_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal result = {0};
  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;
  float res_float = 0.0;

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_sub(tmp1, ten, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, random_pos_int - 10);

  memset(&result, 0, sizeof(result));
  memset(&tmp1, 0, sizeof(tmp1));
  s21_sub(zero, negative_zero, &result);
  res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_sub(zero, tmp1, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0 - random_pos_int);

  memset(&result, 0, sizeof(result));
  memset(&tmp1, 0, sizeof(tmp1));
  res = 0;
  s21_from_int_to_decimal(random_neg_int, &tmp1);
  s21_sub(zero, tmp1, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0 - random_neg_int);

  memset(&result, 0, sizeof(result));
  memset(&tmp1, 0, sizeof(tmp1));
  res = 0;
  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  s21_sub(tmp1, tmp2, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, random_pos_int - random_neg_int);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_sub(one, other_ten, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -9);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_sub(ten, other_ten, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);

  memset(&result, 0, sizeof(result));
  res = 0;
  s21_sub(ten, other_ten_neg, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 20);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  memset(&result, 0, sizeof(result));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  s21_sub(tmp1, tmp2, &result);
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq_tol(res_float, random_pos_float - random_pos_float2,
                         1e-02);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  memset(&result, 0, sizeof(result));
  s21_from_float_to_decimal(random_neg_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float2, &tmp2);
  s21_sub(tmp1, tmp2, &result);
  s21_from_decimal_to_float(result, &res_float);
  ck_assert_float_eq_tol(res_float, random_neg_float - random_neg_float2,
                         1e-02);

  memset(&result, 0, sizeof(result));
  s21_sub(big_num_positive, zero, &result);
  ck_assert_int_eq(result.bits[0], big_num_positive.bits[0]);
  ck_assert_int_eq(result.bits[1], big_num_positive.bits[1]);
  ck_assert_int_eq(result.bits[2], big_num_positive.bits[2]);
  ck_assert_int_eq(result.bits[3], big_num_positive.bits[3]);

  memset(&result, 0, sizeof(result));
  s21_sub(big_num_negative, big_num_negative, &result);
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);

  memset(&result, 0, sizeof(result));
  res = s21_sub(long_num_positive, long_num_negative, &result);
  ck_assert_int_eq(res, 0);

  memset(&result, 0, sizeof(result));
  res = s21_sub(big_num_negative, long_num_positive, &result);
  ck_assert_int_eq(2, res);
}
END_TEST

START_TEST(not_equal_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale= 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  res = s21_is_not_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float, &tmp2);
  res = s21_is_not_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  float num1 = 178.987;
  float num2 = 178.987;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(num1, &tmp1);
  s21_from_float_to_decimal(num2, &tmp2);
  res = s21_is_not_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  res = s21_is_not_equal(zero, negative_zero);
  ck_assert_int_eq(res, 0);

  res = s21_is_not_equal(big_num_negative, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_not_equal(long_num_negative, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_not_equal(big_num_positive, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_not_equal(one, ten);
  ck_assert_int_eq(res, 1);

  res = s21_is_not_equal(other_ten, other_ten_neg);
  ck_assert_int_eq(res, 1);

  res = s21_is_not_equal(ten, other_ten);
  ck_assert_int_eq(res, 0);

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_not_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  s21_from_int_to_decimal(random_neg_float2, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_not_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  int num_int1 = 300000;
  int num_int2 = 3;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_not_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  num_int1 = -5;
  num_int2 = -5;
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_not_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(equal_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale= 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  res = s21_is_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float, &tmp2);
  res = s21_is_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  float num1 = 178.987;
  float num2 = 178.987;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(num1, &tmp1);
  s21_from_float_to_decimal(num2, &tmp2);
  res = s21_is_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  res = s21_is_equal(zero, negative_zero);
  ck_assert_int_eq(res, 1);

  res = s21_is_equal(big_num_negative, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_equal(long_num_negative, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_equal(big_num_positive, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_equal(one, ten);
  ck_assert_int_eq(res, 0);

  res = s21_is_equal(other_ten, other_ten_neg);
  ck_assert_int_eq(res, 0);

  res = s21_is_equal(ten, other_ten);
  ck_assert_int_eq(res, 1);

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  s21_from_int_to_decimal(random_neg_float2, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  int num_int1 = 300000;
  int num_int2 = 3;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  num_int1 = -5;
  num_int2 = -5;
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale= 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  res = s21_is_less(tmp1, tmp2);
  ck_assert_int_eq(res, random_pos_float < random_pos_float2);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float, &tmp2);
  res = s21_is_less(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  float num1 = 178.987;
  float num2 = 178.987;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(num1, &tmp1);
  s21_from_float_to_decimal(num2, &tmp2);
  res = s21_is_less(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  res = s21_is_less(zero, negative_zero);
  ck_assert_int_eq(res, 0);

  res = s21_is_less(big_num_negative, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_less(long_num_negative, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_less(big_num_positive, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_less(one, ten);
  ck_assert_int_eq(res, 1);

  res = s21_is_less(other_ten, other_ten_neg);
  ck_assert_int_eq(res, 0);

  res = s21_is_less(ten, other_ten);
  ck_assert_int_eq(res, 0);

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_less(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  s21_from_int_to_decimal(random_neg_float2, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_less(tmp1, tmp2);
  ck_assert_int_eq(res, random_neg_float2 < random_neg_int);

  int num_int1 = 300000;
  int num_int2 = 3;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_less(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  num_int1 = -5;
  num_int2 = -5;
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_less(tmp1, tmp2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale= 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  res = s21_is_less_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, random_pos_float <= random_pos_float2);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float, &tmp2);
  res = s21_is_less_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  float num1 = 178.987;
  float num2 = 178.987;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(num1, &tmp1);
  s21_from_float_to_decimal(num2, &tmp2);
  res = s21_is_less_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  res = s21_is_less_or_equal(zero, negative_zero);
  ck_assert_int_eq(res, 1);

  res = s21_is_less_or_equal(big_num_negative, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_less_or_equal(long_num_negative, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_less_or_equal(big_num_positive, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_less_or_equal(one, ten);
  ck_assert_int_eq(res, 1);

  res = s21_is_less_or_equal(other_ten, other_ten_neg);
  ck_assert_int_eq(res, 0);

  res = s21_is_less_or_equal(ten, other_ten);
  ck_assert_int_eq(res, 1);

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_less_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  s21_from_int_to_decimal(random_neg_float2, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_less_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, random_neg_float2 <= random_neg_int);

  int num_int1 = 300000;
  int num_int2 = 3;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_less_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  num_int1 = -5;
  num_int2 = -5;
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_less_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale= 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  res = s21_is_greater(tmp1, tmp2);
  ck_assert_int_eq(res, random_pos_float > random_pos_float2);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float, &tmp2);
  res = s21_is_greater(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  float num1 = 178.987;
  float num2 = 178.987;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(num1, &tmp1);
  s21_from_float_to_decimal(num2, &tmp2);
  res = s21_is_greater(tmp1, tmp2);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater(zero, negative_zero);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater(big_num_negative, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater(long_num_negative, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater(big_num_positive, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_greater(one, ten);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater(other_ten, other_ten_neg);
  ck_assert_int_eq(res, 1);

  res = s21_is_greater(ten, other_ten);
  ck_assert_int_eq(res, 0);

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_greater(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  s21_from_int_to_decimal(random_neg_float2, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_greater(tmp1, tmp2);
  ck_assert_int_eq(res, random_neg_float2 > random_neg_int);

  int num_int1 = 300000;
  int num_int2 = 3;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_greater(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  num_int1 = -5;
  num_int2 = -5;
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_greater(tmp1, tmp2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_or_equal_Test) {
  s21_decimal zero = {0};
  s21_decimal negative_zero = {0};
  negative_zero.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal big_num_positive = {0};
  big_num_positive.bits[0] = UINT_MAX;
  big_num_positive.bits[1] = UINT_MAX;
  big_num_positive.bits[2] = UINT_MAX;
  big_num_positive.bits[3] = 0;
  s21_decimal big_num_negative = {0};
  big_num_negative.bits[0] = UINT_MAX;
  big_num_negative.bits[1] = UINT_MAX;
  big_num_negative.bits[2] = UINT_MAX;
  big_num_negative.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal long_num_positive = {0};
  long_num_positive.bits[0] = UINT_MAX;
  long_num_positive.bits[1] = UINT_MAX;
  long_num_positive.bits[2] = UINT_MAX;
  long_num_positive.bits[3] = 0b00000000000111000000000000000000;  // scale= 28
  s21_decimal long_num_negative = {0};
  long_num_negative.bits[0] = UINT_MAX;
  long_num_negative.bits[1] = UINT_MAX;
  long_num_negative.bits[2] = UINT_MAX;
  long_num_negative.bits[3] = 0b10000000000111000000000000000000;  // scale = 28
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  s21_decimal other_ten = {0};
  other_ten.bits[0] = 10000000;
  other_ten.bits[3] = 0b00000000000001100000000000000000;  // scale = 6
  s21_decimal other_ten_neg = {0};
  other_ten_neg.bits[0] = 10000000;
  other_ten_neg.bits[3] = 0b10000000000001100000000000000000;  // scale = 6
  int random_pos_int = 2345;
  int random_neg_int = -2345;
  float random_pos_float = 6545.45456;
  float random_pos_float2 = 22.98236;
  float random_neg_float = -6545.45456;
  float random_neg_float2 = -65.12345;

  s21_decimal tmp1 = {0};
  s21_decimal tmp2 = {0};
  int res = 0;

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_pos_float2, &tmp2);
  res = s21_is_greater_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, random_pos_float >= random_pos_float2);

  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(random_pos_float, &tmp1);
  s21_from_float_to_decimal(random_neg_float, &tmp2);
  res = s21_is_greater_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  float num1 = 178.987;
  float num2 = 178.987;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_float_to_decimal(num1, &tmp1);
  s21_from_float_to_decimal(num2, &tmp2);
  res = s21_is_greater_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  res = s21_is_greater_or_equal(zero, negative_zero);
  ck_assert_int_eq(res, 1);

  res = s21_is_greater_or_equal(big_num_negative, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater_or_equal(long_num_negative, long_num_positive);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater_or_equal(big_num_positive, long_num_positive);
  ck_assert_int_eq(res, 1);

  res = s21_is_greater_or_equal(one, ten);
  ck_assert_int_eq(res, 0);

  res = s21_is_greater_or_equal(other_ten, other_ten_neg);
  ck_assert_int_eq(res, 1);

  res = s21_is_greater_or_equal(ten, other_ten);
  ck_assert_int_eq(res, 1);

  s21_from_int_to_decimal(random_pos_int, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_greater_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  s21_from_int_to_decimal(random_neg_float2, &tmp1);
  s21_from_int_to_decimal(random_neg_int, &tmp2);
  res = s21_is_greater_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, random_neg_float2 >= random_neg_int);

  int num_int1 = 300000;
  int num_int2 = 3;
  memset(&tmp1, 0, sizeof(tmp1));
  memset(&tmp2, 0, sizeof(tmp2));
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_greater_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);

  num_int1 = -5;
  num_int2 = -5;
  s21_from_int_to_decimal(num_int1, &tmp1);
  s21_from_int_to_decimal(num_int2, &tmp2);
  res = s21_is_greater_or_equal(tmp1, tmp2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(simple_round) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;
  init(&ans);

  // -39
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00100111
  // 10000000 00000000 00000000 00000000
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 39;
  true_ans.bits[3] = MINUS;

  int status = s21_round(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_round2) {
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 42;

  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 42;

  int status = s21_round(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_floor) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;
  init(&ans);

  // -40
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 40;
  true_ans.bits[3] = MINUS;

  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_floor_2) {
  // 0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;

  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 0;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_floor_3) {
  // -0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 10000000 00011010 00000000 00000000
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936 + MINUS;

  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 1;
  true_ans.bits[3] = MINUS;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_floor_4) {
  // -263814.1627387128
  // 00000000 00001001 01011111 01100000
  // 00110110 10010001 01001100 11111000
  // 10000000 00001010 00000000 00000000
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 915492088;
  dec.bits[1] = 614240;
  dec.bits[3] = 655360 + MINUS;

  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 263815;
  true_ans.bits[3] = MINUS;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(math_floor) {
  // 0.49999999999999999
  // 00000000 10110001 10100010 10111100
  // 00101110 11000100 11111111 11111111
  // 00000000 00010001 00000000 00000000
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;

  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 0;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(floor_on_int) {
  // -2179
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 2179;
  dec.bits[3] = MINUS;

  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 2179;
  true_ans.bits[3] = MINUS;
  int status = s21_floor(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_truncate) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;
  init(&ans);

  // -39
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00100111
  // 10000000 00000000 00000000 00000000
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 39;
  true_ans.bits[3] = MINUS;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_truncate_2) {
  s21_decimal dec;
  init(&dec);
  // 613478.421
  dec.bits[0] = 613478421;
  dec.bits[3] = 196608;  // точка после третьего знака
  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 613478;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(zero_truncate) {
  s21_decimal dec;
  init(&dec);
  dec.bits[0] = 0;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 196608;

  s21_decimal ans;
  init(&ans);

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 0;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(s21_negate_1) {
  s21_decimal dec;
  s21_decimal ans;
  init(&dec);
  dec.bits[0] = 2814903;
  dec.bits[3] = 65536 + MINUS;

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[3] = 65536;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal dec;
  s21_decimal ans;
  init(&dec);
  dec.bits[0] = 2814903;
  dec.bits[1] = 2384901;
  dec.bits[2] = 27498;
  dec.bits[3] = 0;

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[1] = 2384901;
  true_ans.bits[2] = 27498;
  true_ans.bits[3] = MINUS;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(short_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 65536;
  dec2.bits[0] = 2;
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 32768;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 9;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 6;
  dec2.bits[3] = 65536;
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 15;
  true_ans.bits[3] = 65536;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 14;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 9;
  dec2.bits[3] = 65536;
  // 14/9 = 1.5555555555 5555555555 55555556
  // 00110010 01000011 01000001 00000100
  // 01100000 10101011 01011001 00001000
  // 11000011 10001110 00111000 11100100
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 3280877796;
  true_ans.bits[1] = 1621842184;
  true_ans.bits[2] = 843268356;
  true_ans.bits[3] = 1835008;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 14;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 9;
  dec2.bits[3] = 65536 + MINUS;
  // 14/(-9) = -1.5555555555 5555555555 55555556
  // 00110010 01000011 01000001 00000100
  // 01100000 10101011 01011001 00001000
  // 11000011 10001110 00111000 11100100
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 3280877796;
  true_ans.bits[1] = 1621842184;
  true_ans.bits[2] = 843268356;
  true_ans.bits[3] = 1835008 + MINUS;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(div_by_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 2814903;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 0;
  dec2.bits[3] = 65536 + MINUS;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 3;  // не надо делить на ноль
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(result_too_big) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 1;
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(result_too_small) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec2.bits[0] = 4294967294;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967295;
  dec1.bits[0] = 1;
  dec1.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 2;
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec1.bits[3] = 1179648;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 4294967295;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 4294967295;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967295;

  int status = s21_div(dec1, dec2, &ans);
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 1;
  true_ans.bits[1] = 0;
  true_ans.bits[2] = 0;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  init(&ans);
  // -278576982813512.8359044835908 / 7123984713482.41253 =
  // -39.104096094745301845239149102

  // -278576982813512.8359044835908
  // 00001001 00000000 01010101 10110100
  // 11111100 01000101 01100100 00011110
  // 01110111 00000010 11101010 01000100
  // 10000000 00001101 00000000 00000000
  dec1.bits[0] = 1996679748;
  dec1.bits[1] = 4232406046;
  dec1.bits[2] = 151016884;
  dec1.bits[3] = 2148335616;

  // 7123984713482.41253
  // 00000000 00000000 00000000 00000000
  // 00001001 11100010 11110010 10100010
  // 10011111 00111110 01000011 01100101
  // 00000000 00000101 00000000 00000000
  dec2.bits[0] = 2671657829;
  dec2.bits[1] = 165868194;
  dec2.bits[2] = 0;
  dec2.bits[3] = 327680;

  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 178532910;
  true_ans.bits[1] = 4081246736;
  true_ans.bits[2] = 2119837296;
  true_ans.bits[3] = 2149253120;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}

START_TEST(big_values_div_4) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  init(&ans);
  // 7813912341.293481290382 / 1236128761234.217489792347 =
  // 0.0063212770273961190138049477

  // 7813912341.293481290382
  // 00000000 00000000 00000001 10100111
  // 10010111 11010001 01000010 10000110
  // 01000110 11010011 01101010 10001110
  // 00000000 00001100 00000000 00000000
  dec1.bits[0] = 1188260494;
  dec1.bits[1] = 2547073670;
  dec1.bits[2] = 423;
  dec1.bits[3] = 786432;

  // 1236128761234.217489792347
  // 00000000 00000001 00000101 11000010
  // 10101100 10100110 11001011 10100111
  // 01100010 11011001 11111101 01011011
  // 00000000 00001100 00000000 00000000
  dec2.bits[0] = 1658453339;
  dec2.bits[1] = 2896612263;
  dec2.bits[2] = 67010;
  dec2.bits[3] = 786432;

  // 0.0063212770273961190138049477
  // 00000000 00110100 01001001 11010011
  // 00100100 10011011 00101100 11110100
  // 10110010 10110011 11110011 11000101
  // 00000000 00011100 00000000 00000000
  // 11010001 00100111 01001100 100100100
  // 11011001 01100111 10100101 100101011
  // 00111111 001111000110
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 2998137798;
  true_ans.bits[1] = 614149364;
  true_ans.bits[2] = 3426771;
  true_ans.bits[3] = 1835008;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}

START_TEST(div_test_1) {
  int num1 = 100;
  int num2 = 50;
  int res_origin = 2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_2) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -16384;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_3) {
  int num1 = 2;
  int num2 = 2;
  int res_origin = 1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_4) {
  int num1 = 0;
  int num2 = 5;
  int res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_5) {
  float num1 = 9403.0e2;
  int num2 = 202;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_test_6) {
  float num1 = -9403.0e2;
  float num2 = -2020.29;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_test_7) {
  float num1 = -9403.0e2;
  float num2 = 2020.29;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_test_8) {
  float num1 = -9403.0e2;
  float num2 = 2.28e17;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_test_9) {
  float num1 = -0.9;
  float num2 = 30.323;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal dec1 = {{100, 0, 0, 0}};
  s21_decimal dec2 = {{99999, 0, 0, 0}};

  float res_s21 = 0;
  float res = 100.0 / 99999.0;

  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  float tmp2 = 999.99;
  float res_s21 = 0.0;
  float res = 0.100001;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_float_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_12) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  float res_s21 = 0;
  float res = 0.00100001;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal dec1 = {{10.0e3, 0, 0, 0}};
  s21_decimal dec2 = {{2.00e2, 0, 0, 0}};

  int res_s21 = 0;
  int res = 50;

  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(s21_div_null_14) {
  s21_decimal dec1 = {{1110, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};

  s21_decimal res1;
  int res = s21_div(dec1, dec2, &res1);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(div_test_15) {
  float num1 = -0.9e3;
  float num2 = 30.32;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_test_16) {
  float num1 = -0.9;
  float num2 = 0.000076;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(div_test_17) {
  float num1 = 7922816251424545754;
  float num2 = 34;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_float = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_int_eq(res_float, res_origin);
}
END_TEST

START_TEST(basic_mod) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  dec1.bits[0] = 10;
  dec2.bits[0] = 4;
  // 10 % 4 = 2

  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 2;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_mod_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  // 164471392.8219 % -2829034.112383 = 387414.303686

  // 164471392.8219
  // 00000000 00000000 00000001 01111110
  // 11110000 10010110 11100110 00011011
  // 00000000 00000100 00000000 00000000
  dec1.bits[0] = 4036421147;
  dec1.bits[1] = 382;
  dec1.bits[3] = 262144;

  // -2829034.112383
  // 00000000 00000000 00000010 10010010
  // 10101111 10010010 11000101 01111111
  // 10000000 00000110 00000000 00000000
  dec2.bits[0] = 2945631615;
  dec2.bits[1] = 658;
  dec2.bits[3] = 2147876864;

  // 387414.303686
  // 00000000 00000000 00000000 01011010
  // 00110011 10110001 00100011 11000110
  // 00000000 00000110 00000000 00000000
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 867247046;
  true_ans.bits[1] = 90;
  true_ans.bits[3] = 393216;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_mod_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  init(&ans);
  // -1624980713402947.82193 % 85460968.29048340298 = -53115272.67168058004

  // -1624980713402947.82193
  // 00000000 00000000 00000000 00001000
  // 11001111 00011101 00011110 11101110
  // 10101100 01011010 10111100 11110001
  // 10000000 00000101 00000000 00000000
  dec1.bits[0] = 2891627761;
  dec1.bits[1] = 3474792174;
  dec1.bits[2] = 8;
  dec1.bits[3] = 2147811328;

  // 85460968.29048340298
  // 01110110 10011001 11010101 11001001
  // 01101111 10000100 10111111 01001010
  // 00000000 00001011 00000000 00000000
  dec2.bits[0] = 1870970698;
  dec2.bits[1] = 1989793225;
  dec2.bits[3] = 720896;

  // -53115272.67168058004
  // 01001001 10110110 01010101 11101000
  // 01100110 01011010 01111010 10010100
  // 10000000 00001011 00000000 00000000
  s21_decimal true_ans;
  init(&true_ans);
  true_ans.bits[0] = 1717205652;
  true_ans.bits[1] = 1236686312;
  true_ans.bits[3] = 720896 + MINUS;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(division_on_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  init(&ans);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 0;
  dec2.bits[3] = 196608;

  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 3;  // операция прошла успешно

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(division_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  init(&dec1);
  init(&dec2);
  init(&ans);
  dec1.bits[0] = 0;
  dec1.bits[3] = 196608;

  dec2.bits[0] = 217948;
  dec2.bits[3] = 196608;

  s21_decimal true_ans;
  init(&true_ans);
  int status = s21_mod(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(s21_mod_1) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  setScale(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  setScale(&value_2, 2);
  s21_decimal check = {{91, 0, 0, 0}};
  setScale(&check, 2);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_2) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  setScale(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  setScale(&value_2, 2);
  s21_decimal check = {{0, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_mod_3) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  setScale(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  setScale(&value_2, 2);
  setSign(&value_2, 1);
  s21_decimal check = {{91, 0, 0, 0}};
  setScale(&check, 2);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_4) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  setScale(&value_1, 1);
  setSign(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  setScale(&value_2, 2);
  s21_decimal check = {{91, 0, 0, 0}};
  setScale(&check, 2);
  setSign(&check, 1);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_5) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  setScale(&value_1, 1);
  setSign(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  setScale(&value_2, 2);
  setSign(&value_2, 1);
  s21_decimal check = {{91, 0, 0, 0}};
  setScale(&check, 2);
  setSign(&check, 1);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_6) {
  s21_decimal src1, src2, res_mod;
  int a = -98765;
  int b = 1234;
  int res_origin = a % b;
  int res = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_int(res_mod, &res);
  ck_assert_int_eq(res_origin, res);
}
END_TEST

START_TEST(s21_mod_7) {
  s21_decimal src1, src2, res_mod;
  float a = 1.2;
  float b = 0.3;
  float res_origin = fmod(a, b);
  float res = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_mod(src1, src2, &res_mod);
  s21_from_decimal_to_float(res_mod, &res);
  ck_assert_float_eq(res_origin, res);
}
END_TEST

//-------------//

START_TEST(s21_div_1) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  setScale(&value_1, 1);
  setScale(&value_2, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, 0}};
  setSign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  setSign(&check, 1);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  setSign(&value_1, 1);
  s21_decimal value_2 = {{8, 0, 0, 0}};
  setSign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{125, 0, 0, 0}};
  setScale(&check, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  setSign(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  setScale(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal src1, src2;
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 4654.950495049504950495049505;
  s21_decimal res_od;
  s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_7) {
  s21_decimal src1, src2;
  float a = -9403.0e2;
  float b = -2020.29;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 465.4282306005573457275935633;
  s21_decimal res_od;
  s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal src1, src2;
  float a = -9403.0e20;
  float b = 2.28e17;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  s21_decimal res_od;
  s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal src1, src2;
  src1.bits[0] = 0b00010001100000110100010101000111;
  src1.bits[1] = 0b00000000000000101011011100110010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001010000000000000000;
  src2.bits[0] = 0b01111001000001000011011001001011;
  src2.bits[1] = 0b00000000000000000101010011111111;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000001010000000000000000;
  s21_decimal result_origin;
  result_origin.bits[0] = 0b01000111110000001001001101101011;
  result_origin.bits[1] = 0b10111000000101111000101110100000;
  result_origin.bits[2] = 0b00011010011011010111110000110100;
  result_origin.bits[3] = 0b00000000000110110000000000000000;
  s21_decimal res_od;
  s21_div(src1, src2, &res_od);
  float a, b;
  s21_from_decimal_to_float(result_origin, &a);
  s21_from_decimal_to_float(res_od, &b);
  ck_assert_float_eq(a, b);
}
END_TEST

int main(void) {
  Suite *suite =
      suite_create("S21_TEST");  // создание наборов тестов и с именем S21_TEST
  SRunner *srunner = srunner_create(suite);

  TCase *negate1 = tcase_create("round_simple");
  suite_add_tcase(suite, negate1);
  tcase_add_test(negate1, s21_negate_1);

  TCase *negate2 = tcase_create("round_simple");
  suite_add_tcase(suite, negate2);
  tcase_add_test(negate2, s21_negate_2);

  TCase *truncate_simple = tcase_create("round_simple");
  suite_add_tcase(suite, truncate_simple);
  tcase_add_test(truncate_simple, simple_truncate);

  TCase *truncate_simple2 = tcase_create("round_simple");
  suite_add_tcase(suite, truncate_simple2);
  tcase_add_test(truncate_simple2, simple_truncate_2);

  TCase *truncate_zer = tcase_create("round_simple");
  suite_add_tcase(suite, truncate_zer);
  tcase_add_test(truncate_zer, zero_truncate);

  TCase *round_simple = tcase_create("round_simple");
  suite_add_tcase(suite, round_simple);
  tcase_add_test(round_simple, simple_round);

  TCase *round_simple2 = tcase_create("round_simple2");
  suite_add_tcase(suite, round_simple2);
  tcase_add_test(round_simple2, simple_round2);

  TCase *floor_simple = tcase_create("floor_simple");
  suite_add_tcase(suite, floor_simple);
  tcase_add_test(floor_simple, simple_floor);

  TCase *floor_simple2 = tcase_create("floor_simple");
  suite_add_tcase(suite, floor_simple2);
  tcase_add_test(floor_simple2, simple_floor_2);

  TCase *floor_simple3 = tcase_create("floor_simple");
  suite_add_tcase(suite, floor_simple3);
  tcase_add_test(floor_simple3, simple_floor_3);

  TCase *floor_simple4 = tcase_create("floor_simple");
  suite_add_tcase(suite, floor_simple4);
  tcase_add_test(floor_simple4, simple_floor_4);

  TCase *floor_math = tcase_create("floor_simple");
  suite_add_tcase(suite, floor_math);
  tcase_add_test(floor_math, math_floor);

  TCase *floor_int = tcase_create("floor_simple");
  suite_add_tcase(suite, floor_int);
  tcase_add_test(floor_int, floor_on_int);

  TCase *mul_Test = tcase_create("mul_test");
  // создание тестового примера с именем
  suite_add_tcase(suite, mul_Test);  // добавление в тестовый набор
  tcase_add_test(mul_Test, mul_test);
  // добавление тестовой функции в тестовый пример

  TCase *convert_Test = tcase_create("convert_test");
  suite_add_tcase(suite, convert_Test);
  tcase_add_test(convert_Test, convert_test);
  TCase *s21add_test =
      tcase_create("s21add");  // создание тестового примера с именем s21add
  suite_add_tcase(suite, s21add_test);  // добавление в тестовый набор
  tcase_add_test(s21add_test,
                 add_Test);  // добавление тестовой функции в тестовый пример

  TCase *s21sub_test = tcase_create("s21sub");
  suite_add_tcase(suite, s21sub_test);
  tcase_add_test(s21sub_test, sub_Test);

  TCase *s21not_equal = tcase_create("s21not_equal");
  suite_add_tcase(suite, s21not_equal);
  tcase_add_test(s21not_equal, not_equal_Test);

  TCase *s21equal_test = tcase_create("s21equal");
  suite_add_tcase(suite, s21equal_test);
  tcase_add_test(s21equal_test, equal_Test);

  TCase *s21less_test = tcase_create("s21less");
  suite_add_tcase(suite, s21less_test);
  tcase_add_test(s21less_test, less_Test);

  TCase *s21less_or_equal = tcase_create("s21less_or_equal");
  suite_add_tcase(suite, s21less_or_equal);
  tcase_add_test(s21less_or_equal, less_or_equal_Test);

  TCase *s21greater = tcase_create("s21greater");
  suite_add_tcase(suite, s21greater);
  tcase_add_test(s21greater, greater_Test);

  TCase *s21greater_or_equal = tcase_create("s21greater_or_equal");
  suite_add_tcase(suite, s21greater_or_equal);
  tcase_add_test(s21greater_or_equal, greater_or_equal_Test);

  TCase *s21_division_1 = tcase_create("s21_division_1");
  suite_add_tcase(suite, s21_division_1);
  tcase_add_test(s21_division_1, s21_div_1);

  TCase *s21_division_2 = tcase_create("s21_division_2");
  suite_add_tcase(suite, s21_division_2);
  tcase_add_test(s21_division_2, s21_div_2);

  TCase *s21_division_3 = tcase_create("s21_division_3");
  suite_add_tcase(suite, s21_division_3);
  tcase_add_test(s21_division_3, s21_div_3);

  TCase *s21_division_4 = tcase_create("s21_division_4");
  suite_add_tcase(suite, s21_division_4);
  tcase_add_test(s21_division_4, s21_div_4);

  TCase *s21_division_5 = tcase_create("s21_division_5");
  suite_add_tcase(suite, s21_division_5);
  tcase_add_test(s21_division_5, s21_div_5);

  TCase *s21_division_6 = tcase_create("s21_division_6");
  suite_add_tcase(suite, s21_division_6);
  tcase_add_test(s21_division_6, s21_div_6);

  TCase *s21_division_7 = tcase_create("s21_division_7");
  suite_add_tcase(suite, s21_division_7);
  tcase_add_test(s21_division_7, s21_div_7);

  TCase *s21_division_8 = tcase_create("s21_division_8");
  suite_add_tcase(suite, s21_division_8);
  tcase_add_test(s21_division_8, s21_div_8);

  TCase *s21_division_9 = tcase_create("s21_division_9");
  suite_add_tcase(suite, s21_division_9);
  tcase_add_test(s21_division_9, s21_div_9);

  TCase *mod_1 = tcase_create("mod_1");
  suite_add_tcase(suite, mod_1);
  tcase_add_test(mod_1, s21_mod_1);

  TCase *mod_2 = tcase_create("mod_2");
  suite_add_tcase(suite, mod_2);
  tcase_add_test(mod_2, s21_mod_2);

  TCase *mod_3 = tcase_create("mod_3");
  suite_add_tcase(suite, mod_3);
  tcase_add_test(mod_3, s21_mod_3);

  TCase *mod_4 = tcase_create("mod_4");
  suite_add_tcase(suite, mod_4);
  tcase_add_test(mod_4, s21_mod_4);

  TCase *mod_5 = tcase_create("mod_5");
  suite_add_tcase(suite, mod_5);
  tcase_add_test(mod_5, s21_mod_5);

  TCase *mod_6 = tcase_create("mod_6");
  suite_add_tcase(suite, mod_6);
  tcase_add_test(mod_6, s21_mod_6);

  TCase *mod_7 = tcase_create("mod_7");
  suite_add_tcase(suite, mod_7);
  tcase_add_test(mod_7, s21_mod_7);

  TCase *mod_simple = tcase_create("mod_simple");
  suite_add_tcase(suite, mod_simple);
  tcase_add_test(mod_simple, basic_mod);

  TCase *mod_simple2 = tcase_create("mod_simple2");
  suite_add_tcase(suite, mod_simple2);
  tcase_add_test(mod_simple2, basic_mod_2);

  TCase *mod_simple3 = tcase_create("mod_simple3");
  suite_add_tcase(suite, mod_simple3);
  tcase_add_test(mod_simple3, basic_mod_3);

  TCase *mod_simple5 = tcase_create("mod_simple5");
  suite_add_tcase(suite, mod_simple5);
  tcase_add_test(mod_simple5, division_on_zero);

  TCase *mod_simple6 = tcase_create("mod_simple6");
  suite_add_tcase(suite, mod_simple6);
  tcase_add_test(mod_simple6, division_zero);

  TCase *div_1 = tcase_create("div_1");
  suite_add_tcase(suite, div_1);
  tcase_add_test(div_1, div_test_1);

  TCase *div_2 = tcase_create("div_2");
  suite_add_tcase(suite, div_2);
  tcase_add_test(div_2, div_test_2);

  TCase *div_3 = tcase_create("div_3");
  suite_add_tcase(suite, div_3);
  tcase_add_test(div_3, div_test_3);

  TCase *div_4 = tcase_create("div_4");
  suite_add_tcase(suite, div_4);
  tcase_add_test(div_4, div_test_4);

  TCase *div_5 = tcase_create("div_5");
  suite_add_tcase(suite, div_5);
  tcase_add_test(div_5, div_test_5);

  TCase *div_6 = tcase_create("div_6");
  suite_add_tcase(suite, div_6);
  tcase_add_test(div_6, div_test_6);

  TCase *div_7 = tcase_create("div_7");
  suite_add_tcase(suite, div_7);
  tcase_add_test(div_7, div_test_7);

  TCase *div_8 = tcase_create("div_8");
  suite_add_tcase(suite, div_8);
  tcase_add_test(div_8, div_test_8);

  TCase *div_9 = tcase_create("div_9");
  suite_add_tcase(suite, div_9);
  tcase_add_test(div_9, div_test_9);

  TCase *div_10 = tcase_create("div_10");
  suite_add_tcase(suite, div_10);
  tcase_add_test(div_10, s21_div_10);

  TCase *div_11 = tcase_create("div_11");
  suite_add_tcase(suite, div_11);
  tcase_add_test(div_11, s21_div_11);

  TCase *div_12 = tcase_create("div_12");
  suite_add_tcase(suite, div_12);
  tcase_add_test(div_12, s21_div_12);

  TCase *div_13 = tcase_create("div_13");
  suite_add_tcase(suite, div_13);
  tcase_add_test(div_13, s21_div_13);

  TCase *div_14 = tcase_create("div_14");
  suite_add_tcase(suite, div_14);
  tcase_add_test(div_14, s21_div_null_14);

  TCase *div_15 = tcase_create("div_15");
  suite_add_tcase(suite, div_15);
  tcase_add_test(div_15, div_test_15);

  TCase *div_16 = tcase_create("div_16");
  suite_add_tcase(suite, div_16);
  tcase_add_test(div_16, div_test_16);

  TCase *div_17 = tcase_create("div_17");
  suite_add_tcase(suite, div_17);
  tcase_add_test(div_17, div_test_17);

  TCase *div_sh = tcase_create("div_shor");
  suite_add_tcase(suite, div_sh);
  tcase_add_test(div_sh, short_div);

  TCase *div_basic = tcase_create("div_basc");
  suite_add_tcase(suite, div_basic);
  tcase_add_test(div_basic, basic_div);

  TCase *div_basic2 = tcase_create("div_bas2");
  suite_add_tcase(suite, div_basic2);
  tcase_add_test(div_basic2, basic_div_2);

  TCase *div_basic3 = tcase_create("div_bas3");
  suite_add_tcase(suite, div_basic3);
  tcase_add_test(div_basic3, basic_div_3);

  TCase *div_0 = tcase_create("div_0");
  suite_add_tcase(suite, div_0);
  tcase_add_test(div_0, div_by_zero);

  TCase *div_big = tcase_create("div_big");
  suite_add_tcase(suite, div_big);
  tcase_add_test(div_big, result_too_big);

  TCase *div_small = tcase_create("div_small");
  suite_add_tcase(suite, div_small);
  tcase_add_test(div_small, result_too_small);

  TCase *div_bigg = tcase_create("div_bigg");
  suite_add_tcase(suite, div_bigg);
  tcase_add_test(div_bigg, big_values_div);

  TCase *div_bigg2 = tcase_create("div_bigg");
  suite_add_tcase(suite, div_bigg2);
  tcase_add_test(div_bigg2, big_values_div_2);

  TCase *div_bigg3 = tcase_create("div_bigg");
  suite_add_tcase(suite, div_bigg3);
  tcase_add_test(div_bigg3, big_values_div_3);

  TCase *div_bigg4 = tcase_create("div_bigg");
  suite_add_tcase(suite, div_bigg4);
  tcase_add_test(div_bigg4, big_values_div_4);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
