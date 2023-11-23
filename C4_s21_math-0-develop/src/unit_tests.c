#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

START_TEST(abs_test) {
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(1), abs(1));
  ck_assert_int_eq(s21_abs(-0), abs(-0));
  ck_assert_int_eq(s21_abs(0), abs(0));
  ck_assert_int_eq(s21_abs(-2147483647), abs(-2147483647));
  ck_assert_int_eq(s21_abs(2147483647), abs(2147483647));
}
END_TEST

START_TEST(fabs_test) {
  ck_assert_ldouble_infinite(s21_fabs(s21_INF));
  ck_assert_ldouble_infinite(s21_fabs(-s21_INF));
  ck_assert_ldouble_nan(s21_fabs(s21_NAN));
  ck_assert_ldouble_nan(s21_fabs(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_fabs(0.0), fabs(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-0.0), fabs(-0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-1.0), fabs(-1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(1.0), fabs(1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(0.5), fabs(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-0.5), fabs(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-0.32414), fabs(-0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(0.32414), fabs(0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(123.324242423), fabs(123.324242423), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-123.324242423), fabs(-123.324242423),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(0.000000000001), fabs(0.000000000001),
                           1e-20);
  ck_assert_ldouble_eq_tol(s21_fabs(-0.000000000001), fabs(-0.000000000001),
                           1e-20);
  ck_assert_ldouble_eq_tol(s21_fabs(-2147483647.32414143),
                           fabs(-2147483647.32414143), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(2147483647.32414143),
                           fabs(2147483647.32414143), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-1000.0), fabs(-1000.0), 1e-6);
}
END_TEST

START_TEST(asin_test) {
  ck_assert_ldouble_nan(s21_asin(s21_INF));
  ck_assert_ldouble_nan(s21_asin(-s21_INF));
  ck_assert_ldouble_nan(s21_asin(s21_NAN));
  ck_assert_ldouble_nan(s21_asin(-s21_NAN));
  ck_assert_ldouble_nan(s21_asin(2));
  ck_assert_ldouble_nan(s21_asin(1000));
  ck_assert_ldouble_eq_tol(s21_asin(0.1), asin(0.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0.1), asin(-0.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.32414), asin(0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0.32414), asin(-0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.5), asin(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0.5), asin(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-1), asin(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(1), asin(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0), asin(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0), asin(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.000000000001), asin(0.000000000001),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0.000000000001), asin(-0.000000000001),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0.0002347234), asin(-0.0002347234), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.0002347234), asin(0.0002347234), 1e-6);
}
END_TEST

START_TEST(acos_test) {
  ck_assert_ldouble_nan(s21_acos(s21_INF));
  ck_assert_ldouble_nan(s21_acos(-s21_INF));
  ck_assert_ldouble_nan(s21_acos(s21_NAN));
  ck_assert_ldouble_nan(s21_acos(-s21_NAN));
  ck_assert_ldouble_nan(s21_acos(2));
  ck_assert_ldouble_nan(s21_acos(1000));
  ck_assert_ldouble_eq_tol(s21_acos(0.1), acos(0.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.1), acos(-0.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0.32414), acos(0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.32414), acos(-0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0.5), acos(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.5), acos(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-1), acos(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(1), acos(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0), acos(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0), acos(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0.000000000001), acos(0.000000000001),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.000000000001), acos(-0.000000000001),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0.0002347234), acos(0.0002347234), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.0002347234), acos(-0.0002347234), 1e-6);
}
END_TEST

START_TEST(atan_test) {
  ck_assert_ldouble_nan(s21_atan(s21_NAN));
  ck_assert_ldouble_nan(s21_atan(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_atan(-s21_INF), atan(-s21_INF), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(s21_INF), atan(s21_INF), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.5), atan(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.5), atan(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.1), atan(0.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.1), atan(-0.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-1), atan(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1), atan(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1.555325), atan(1.555325), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-1.555325), atan(-1.555325), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0), atan(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0), atan(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(123.324242423), atan(123.324242423), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.000000000001), atan(0.000000000001),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.000000000001), atan(-0.000000000001),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-65465476545647.4234),
                           atan(-65465476545647.4234), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(65465476545647.4234),
                           atan(65465476545647.4234), 1e-6);
}
END_TEST

START_TEST(floor_test) {
  ck_assert_ldouble_infinite(s21_floor(s21_INF));
  ck_assert_ldouble_infinite(s21_floor(-s21_INF));
  ck_assert_ldouble_nan(s21_floor(s21_NAN));
  ck_assert_ldouble_nan(s21_floor(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_floor(0.0), floor(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-0.0), floor(-0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-1.0), floor(-1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(1.0), floor(1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(0.5), floor(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-0.5), floor(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-0.32414), floor(-0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(0.32414), floor(0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(123.324242423), floor(123.324242423),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-123.324242423), floor(-123.324242423),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(0.000000000001), floor(0.000000000001),
                           1e-20);
  ck_assert_ldouble_eq_tol(s21_floor(-0.000000000001), floor(-0.000000000001),
                           1e-20);
  ck_assert_ldouble_eq_tol(s21_floor(-2147483647.32414143),
                           floor(-2147483647.32414143), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(2147483647.32414143),
                           floor(2147483647.32414143), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-65465476545647.4234),
                           floor(-65465476545647.4234), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(65465476545647.4234),
                           floor(65465476545647.4234), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(1000), floor(1000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-1000), floor(-1000), 1e-6);
}
END_TEST

START_TEST(ceil_test) {
  ck_assert_ldouble_infinite(s21_ceil(s21_INF));
  ck_assert_ldouble_infinite(s21_ceil(-s21_INF));
  ck_assert_ldouble_nan(s21_ceil(s21_NAN));
  ck_assert_ldouble_nan(s21_ceil(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_ceil(0.0), ceil(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-0.0), ceil(-0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-1.0), ceil(-1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(1.0), ceil(1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(0.5), ceil(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-0.5), ceil(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-0.32414), ceil(-0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(0.32414), ceil(0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(123.324242423), ceil(123.324242423), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-123.324242423), ceil(-123.324242423),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(0.000000000001), ceil(0.000000000001),
                           1e-20);
  ck_assert_ldouble_eq_tol(s21_ceil(-0.000000000001), ceil(-0.000000000001),
                           1e-20);
  ck_assert_ldouble_eq_tol(s21_ceil(-2147483647.32414143),
                           ceil(-2147483647.32414143), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(2147483647.32414143),
                           ceil(2147483647.32414143), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-65465476545647.4234),
                           ceil(-65465476545647.4234), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(65465476545647.4234),
                           ceil(65465476545647.4234), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(1000), ceil(1000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-1000), ceil(-1000), 1e-6);
}
END_TEST

START_TEST(exp_test) {
  ck_assert_ldouble_infinite(s21_exp(s21_INF));
  ck_assert_ldouble_eq_tol(s21_exp(-s21_INF), exp(-s21_INF), 1e-6);
  ck_assert_ldouble_nan(s21_exp(s21_NAN));
  ck_assert_ldouble_nan(s21_exp(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_exp(0.5), exp(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-0.5), exp(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-1), exp(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(1), exp(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(0.32414), exp(0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-0.32414), exp(-0.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(1.32414), exp(1.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-1.32414), exp(-1.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(2.32414), exp(2.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-2.32414), exp(-2.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(0), exp(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-0), exp(-0), 1e-6);
  ck_assert_ldouble_infinite(s21_exp(s21_INF));
  ck_assert_ldouble_eq_tol(s21_exp(0.000000000001), exp(0.000000000001), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-0.000000000001), exp(-0.000000000001),
                           1e-6);
}
END_TEST

START_TEST(log_test) {
  ck_assert_ldouble_infinite(s21_log(s21_INF));
  ck_assert_ldouble_nan(s21_log(-s21_INF));
  ck_assert_ldouble_nan(s21_log(s21_NAN));
  ck_assert_ldouble_nan(s21_log(-s21_NAN));
  ck_assert_ldouble_infinite(s21_log(0));
  ck_assert_ldouble_infinite(s21_log(-0));
  ck_assert_ldouble_nan(s21_log(-0.5));
  ck_assert_ldouble_nan(s21_log(-0.156151));
  ck_assert_ldouble_eq_tol(s21_log(0.5), log(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(1), log(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(1.32414), log(1.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(123.324242423), log(123.324242423), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(0.000000000001), log(0.000000000001), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(65465476545647.4234),
                           log(65465476545647.4234), 1e-6);
}
END_TEST

START_TEST(sqrt_test) {
  ck_assert_ldouble_nan(s21_sqrt(-s21_INF));
  ck_assert_ldouble_infinite(s21_sqrt(s21_INF));
  ck_assert_ldouble_nan(s21_sqrt(s21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(-s21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(-0.15615));
  ck_assert_ldouble_nan(s21_sqrt(-121.0));
  ck_assert_ldouble_eq_tol(s21_sqrt(0.5), sqrt(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(1), sqrt(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(1.32414), sqrt(1.32414), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(121.0), sqrt(121.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrt(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(-0), sqrt(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(123.324242423), sqrt(123.324242423), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(0.000000000001), sqrt(0.000000000001),
                           1e-6);
}
END_TEST

START_TEST(pow_test) {
  ck_assert_ldouble_infinite(s21_pow(s21_INF, s21_INF));
  ck_assert_ldouble_infinite(s21_pow(-s21_INF, s21_INF));
  ck_assert_ldouble_infinite(s21_pow(-s21_INF, 2));
  ck_assert_ldouble_infinite(s21_pow(-s21_INF, 1));
  ck_assert_ldouble_infinite(s21_pow(21, s21_INF));
  ck_assert_ldouble_nan(s21_pow(-s21_INF, s21_NAN));
  ck_assert_ldouble_nan(s21_pow(-s21_INF, -s21_NAN));
  ck_assert_ldouble_nan(s21_pow(s21_INF, s21_NAN));
  ck_assert_ldouble_nan(s21_pow(s21_INF, -s21_NAN));
  ck_assert_ldouble_nan(s21_pow(s21_NAN, s21_INF));
  ck_assert_ldouble_nan(s21_pow(s21_NAN, -s21_INF));
  ck_assert_ldouble_nan(s21_pow(s21_NAN, s21_NAN));
  ck_assert_ldouble_nan(s21_pow(s21_NAN, -s21_NAN));
  ck_assert_ldouble_nan(s21_pow(s21_NAN, 2));
  ck_assert_ldouble_nan(s21_pow(s21_NAN, 2));
  ck_assert_ldouble_nan(s21_pow(21, s21_NAN));
  ck_assert_ldouble_nan(s21_pow(21, -s21_NAN));
  ck_assert_ldouble_nan(s21_pow(-21, 0.5));
  ck_assert_ldouble_nan(s21_pow(-21, -0.5));
  ck_assert_ldouble_nan(s21_pow(-21, 1.651651));
  ck_assert_ldouble_nan(s21_pow(-21, -1.651651));
  ck_assert_ldouble_nan(s21_pow(-123.324242423, -1.5));
  ck_assert_ldouble_nan(s21_pow(-123.324242423, 0.21));

  ck_assert_ldouble_eq_tol(s21_pow(s21_INF, -s21_INF), pow(s21_INF, -s21_INF),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(1, -s21_INF), pow(1, -s21_INF), 1e-6);
  ck_assert_ldouble_eq(s21_pow(-s21_INF, -s21_INF), pow(-s21_INF, -s21_INF));
  ck_assert_ldouble_eq_tol(s21_pow(s21_INF, 0), pow(s21_INF, 0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(21, -s21_INF), pow(21, -s21_INF), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(0, 21), pow(0, 21), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(-0, 21), pow(-0, 21), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(21, 0), pow(21, 0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(21, -0), pow(21, -0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(21, 0.5), pow(21, 0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(21, -0.5), pow(21, -0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(-21, 2), pow(-21, 2), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(-21, -2), pow(-21, -2), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(-123.324242423, -1), pow(-123.324242423, -1),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(0.32414, 1), pow(0.32414, 1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(0.32414, 10), pow(0.32414, 10), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(-100.0, 3), pow(-100.0, 3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(-100.0, -3), pow(-100.0, -3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(55.4, 1.5), pow(55.4, 1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(55.4, -1.5), pow(55.4, -1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(8222.3, 2), pow(8222.3, 2), 1e-6);
}
END_TEST

START_TEST(cos_test) {
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 17) {
      ck_assert_double_eq_tol(cos(k + R * s21_PI), s21_cos(k + R * s21_PI),
                              1e-6);
    }
  }
  for (int R = 5; R >= -15; R -= 2) {
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 12) {
      ck_assert_double_eq_tol(cos(k + R * s21_PI), s21_cos(k + R * s21_PI),
                              1e-7);
    }
  }
  ck_assert_ldouble_nan(s21_cos(s21_INF));
  ck_assert_ldouble_nan(s21_cos(-s21_INF));
  ck_assert_ldouble_nan(s21_cos(s21_NAN));
  ck_assert_ldouble_nan(s21_cos(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_cos(0.5), cos(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-0.5), cos(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-1), cos(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(1), cos(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(1.1), cos(1.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(1.5), cos(1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-2.1), cos(-2.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(0), cos(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-0), cos(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(5.123456789123), cos(5.123456789123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(0.00000004564897), cos(0.00000004564897),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(170000.1), cos(170000.1), 1e-6);
}
END_TEST

START_TEST(sin_test) {
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 17) {
      ck_assert_double_eq_tol(sin(k + R * s21_PI), s21_sin(k + R * s21_PI),
                              1e-6);
    }
  }
  for (int R = 5; R >= -15; R -= 2) {
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 15) {
      ck_assert_double_eq_tol(sin(k + R * s21_PI), s21_sin(k + R * s21_PI),
                              1e-7);
    }
  }
  ck_assert_ldouble_nan(s21_sin(s21_INF));
  ck_assert_ldouble_nan(s21_sin(-s21_INF));
  ck_assert_ldouble_nan(s21_sin(s21_NAN));
  ck_assert_ldouble_nan(s21_sin(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_sin(0.5), sin(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-0.5), sin(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-1), sin(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(1), sin(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(1.1), sin(1.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-2.1), sin(-2.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(0), sin(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-0), sin(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(5.123456789123), sin(5.123456789123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(0.00000004564897), sin(0.00000004564897),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(10000000), sin(10000000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-10000000), sin(-10000000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(17000000.1), sin(17000000.1), 1e-6);
}
END_TEST

START_TEST(tan_test) {
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 9) {
      ck_assert_double_eq_tol(tan(k + R * s21_PI), s21_tan(k + R * s21_PI),
                              1e-6);
    }
  }
  ck_assert_ldouble_nan(s21_cos(s21_INF));
  ck_assert_ldouble_nan(s21_cos(-s21_INF));
  ck_assert_ldouble_nan(s21_cos(s21_NAN));
  ck_assert_ldouble_nan(s21_cos(-s21_NAN));
  ck_assert_ldouble_eq_tol(s21_tan(0.5), tan(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-0.5), tan(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-1), tan(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(1), tan(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(1.1), tan(1.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-2.1), tan(-2.1), 1e-8);
  ck_assert_ldouble_eq_tol(s21_tan(0), tan(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-0), tan(-0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(0.00000004564897), tan(0.00000004564897),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(17000000.1), tan(17000000.1), 1e-6);
}
END_TEST

START_TEST(sin_cos_tan_test) {
  ck_assert_double_nan(s21_sin(s21_NAN));
  ck_assert_double_nan(s21_cos(s21_NAN));
  ck_assert_double_nan(s21_tan(s21_NAN));
  ck_assert_double_nan(s21_sin(s21_INF));
  ck_assert_double_nan(s21_cos(s21_INF));
  ck_assert_double_nan(s21_tan(s21_INF));
  ck_assert_double_nan(s21_sin(-s21_INF));
  ck_assert_double_nan(s21_cos(-s21_INF));
  ck_assert_double_nan(s21_tan(-s21_INF));
}
END_TEST

START_TEST(fmod_test) {
  for (double a = -1500; a < 1500; a += 123) {
    for (double b = -12; b < 12; b += 1.25) {
      ck_assert_double_eq(fmod(a, b), s21_fmod(a, b));
      ck_assert_double_eq(fmod(b, a), s21_fmod(b, a));
    }
  }
  ck_assert_double_nan(fmod(1, 0));
  ck_assert_double_nan(s21_fmod(1, 0));
  ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
  ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1));
  ck_assert_double_nan(fmod(INFINITY, -1));
  ck_assert_double_nan(s21_fmod(INFINITY, -1));
  ck_assert_double_eq(fmod(-1, -INFINITY), s21_fmod(-1, -s21_INF));
  ck_assert_double_eq(fmod(0, INFINITY), s21_fmod(0, s21_INF));
  ck_assert_double_nan(s21_fmod(0, s21_NAN));
  ck_assert_double_nan(fmod(0, NAN));
  ck_assert_double_nan(s21_fmod(s21_NAN, s21_NAN));
  ck_assert_double_nan(fmod(NAN, NAN));
  ck_assert_double_nan(s21_fmod(s21_NAN, s21_INF));
  ck_assert_double_nan(s21_fmod(s21_INF, s21_NAN));
  ck_assert_double_nan(s21_fmod(s21_NAN, -s21_INF));
  ck_assert_double_nan(s21_fmod(-s21_INF, s21_NAN));
  ck_assert_double_nan(fmod(NAN, INFINITY));
  ck_assert_double_nan(fmod(INFINITY, NAN));
  ck_assert_double_nan(fmod(NAN, -INFINITY));
  ck_assert_double_nan(fmod(-INFINITY, NAN));
}
END_TEST

int main(void) {
  Suite *suite =
      suite_create("S21_TEST");  // создание наборов тестов и с именем S21_TEST
  SRunner *srunner = srunner_create(suite);

  TCase *abs_Test =
      tcase_create("abs_test");  // создание тестового примера с именем
  suite_add_tcase(suite, abs_Test);  // добавление в тестовый набор
  tcase_add_test(abs_Test,
                 abs_test);  // добавление тестовой функции в тестовый пример

  TCase *fabs_Test = tcase_create("fabs_test");
  suite_add_tcase(suite, fabs_Test);
  tcase_add_test(fabs_Test, fabs_test);

  TCase *asin_Test = tcase_create("asin_test");
  suite_add_tcase(suite, asin_Test);
  tcase_add_test(asin_Test, asin_test);

  TCase *acos_Test = tcase_create("acos_test");
  suite_add_tcase(suite, acos_Test);
  tcase_add_test(acos_Test, acos_test);

  TCase *atan_Test = tcase_create("atan_test");
  suite_add_tcase(suite, atan_Test);
  tcase_add_test(atan_Test, atan_test);

  TCase *floor_Test = tcase_create("floor_test");
  suite_add_tcase(suite, floor_Test);
  tcase_add_test(floor_Test, floor_test);

  TCase *ceil_Test = tcase_create("ceil_test");
  suite_add_tcase(suite, ceil_Test);
  tcase_add_test(ceil_Test, ceil_test);

  TCase *exp_Test = tcase_create("exp_test");
  suite_add_tcase(suite, exp_Test);
  tcase_add_test(exp_Test, exp_test);

  TCase *log_Test = tcase_create("log_test");
  suite_add_tcase(suite, log_Test);
  tcase_add_test(log_Test, log_test);

  TCase *sqrt_Test = tcase_create("sqrt_test");
  suite_add_tcase(suite, sqrt_Test);
  tcase_add_test(sqrt_Test, sqrt_test);

  TCase *pow_Test = tcase_create("pow_test");
  suite_add_tcase(suite, pow_Test);
  tcase_add_test(pow_Test, pow_test);

  TCase *cos_Test = tcase_create("cos_test");
  suite_add_tcase(suite, cos_Test);
  tcase_add_test(cos_Test, cos_test);

  TCase *sin_Test = tcase_create("sin_test");
  suite_add_tcase(suite, sin_Test);
  tcase_add_test(sin_Test, sin_test);

  TCase *tan_Test = tcase_create("tan_test");
  suite_add_tcase(suite, tan_Test);
  tcase_add_test(tan_Test, tan_test);

  TCase *sin_cos_tan_Test = tcase_create("sin_cos_tan_test");
  suite_add_tcase(suite, sin_cos_tan_Test);
  tcase_add_test(sin_cos_tan_Test, sin_cos_tan_test);

  TCase *fmod_Test = tcase_create("fmod_test");
  suite_add_tcase(suite, fmod_Test);
  tcase_add_test(fmod_Test, fmod_test);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
