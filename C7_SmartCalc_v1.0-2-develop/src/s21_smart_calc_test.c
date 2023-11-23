
#include <check.h>

#include "./SmartCalc/s21_calc.h"

START_TEST(test_1) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("10+10-10*10/+2", &num, 0);
  ck_assert_ldouble_eq(num, -30);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_2) {
  long double num = 0;
  long double t = 0;
  int ret = 0;
  ret = s21_smart_calc("sin(10)+cos(sqrt(45))/ln(41)", &num, 0);
  t = sin(10) + cos(sqrt(45)) / log(41);
  // printf("\ndouble = num = %Lf\n", num);
  ck_assert_ldouble_eq_tol(num, t, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_3) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("cos(tan(10))+2.35e5+1.02e-2", &num, 0);
  ck_assert_ldouble_eq_tol(num, cos(tan(10)) + 2.35e5 + 1.02e-2, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_4) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("asin(1)/acos(-1)+atan(0)", &num, 0);
  ck_assert_ldouble_eq_tol(num, asin(1) / acos(-1) + atan(0), 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_5) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("5*)", &num, 0);
  // ck_assert_ldouble_eq(num, 30);
  ck_assert_int_eq(-1, ret);
}
END_TEST

START_TEST(test_6) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("sin15+1542)", &num, 0);
  // ck_assert_ldouble_eq(num, 30);
  ck_assert_int_eq(-1, ret);
}
END_TEST

START_TEST(test_7) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("", &num, 0);
  // ck_assert_ldouble_eq(num, 30);
  ck_assert_int_eq(-1, ret);
}
END_TEST

START_TEST(test_8) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("log(10)*log(10000)/10^2+10%4", &num, 0);
  ck_assert_ldouble_eq_tol(num,
                           log10l(10) * log10l(10000) / pow(10, 2) + 10 % 4, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_9) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("10 10", &num, 0);
  // ck_assert_ldouble_eq_tol(num, log10l(10)*log10l(10000)/pow(10,2), 7);
  ck_assert_int_eq(-1, ret);
}
END_TEST

START_TEST(test_10) {
  long double num = 0;
  int ret = 0;
  ret = s21_smart_calc("asin(10)", &num, 0);
  // ck_assert_ldouble_eq_tol(num, log10l(10)*log10l(10000)/pow(10,2), 7);
  ck_assert_int_eq(-1, ret);
}
END_TEST

START_TEST(test_11) {
  long double num = 0;
  int ret = 0;
  long double x = -2.3;
  ret = s21_smart_calc("x^2+x/(x+1)", &num, x);
  ck_assert_double_eq_tol(num, pow(x, 2) + x / (x + 1), 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_12) {
  long double num = 0;
  int ret = 0;
  long double x = 1000.214;
  ret = s21_smart_calc("cos(x)*sin(x)/log(x)+ln(x)-sqrt(x)*tan(x)", &num, x);
  ck_assert_double_eq_tol(
      num, (cos(x) * sin(x) / log10(x) + log(x) - sqrt(x) * tan(x)), 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_13) {
  credit cr = {0, 0, 0, 0, 0};
  cr = s21_credit(100000.0, 12, 9.5 / 100, 0);
  ck_assert_double_eq_tol(cr.per_month, 8768.38, 2);
  ck_assert_double_eq_tol(cr.pereplata, 5220.20, 2);
  ck_assert_double_eq_tol(cr.sum, 105220.20, 2);
}
END_TEST

START_TEST(test_14) {
  credit cr = {0, 0, 0, 0, 0};
  cr = s21_credit(100, 12, 99 * 0.01, 0);
  ck_assert_double_eq_tol(cr.per_month, 13.44, 2);
  ck_assert_double_eq_tol(cr.pereplata, 61.28, 2);
  ck_assert_double_eq_tol(cr.sum, 161.28, 2);
}
END_TEST

START_TEST(test_15) {
  credit cr = {0, 0, 0, 0, 0};
  cr = s21_credit(0, 0, 0, 0);
  ck_assert_double_eq_tol(cr.per_month, 0.00, 2);
  ck_assert_double_eq_tol(cr.pereplata, 0.00, 2);
  ck_assert_double_eq_tol(cr.sum, 0.00, 2);
}
END_TEST

START_TEST(test_16) {
  credit cr = {0, 0, 0, 0, 0};
  cr = s21_credit(999900, 15 * 12, 84 * 0.01, 1);
  ck_assert_double_eq_tol(cr.per_month_first, 75548.00, 2);
  ck_assert_double_eq_tol(cr.per_month_last, 5943.85, 2);
  ck_assert_double_eq_tol(cr.pereplata, 6334366.50, 2);
  ck_assert_double_eq_tol(cr.sum, 7334266.50, 2);
}
END_TEST

/// log(x)+ln(x)-sqrt(-1*x)*tan(x)

int main(void) {
  Suite *suite =
      suite_create("S21_TEST");  // создание наборов тестов и с именем S21_TEST
  SRunner *srunner = srunner_create(suite);

  TCase *create1 = tcase_create("test_1\t");
  suite_add_tcase(suite, create1);
  tcase_add_test(create1, test_1);

  TCase *create2 = tcase_create("test_2\t");
  suite_add_tcase(suite, create2);
  tcase_add_test(create2, test_2);

  TCase *create3 = tcase_create("test_3\t");
  suite_add_tcase(suite, create3);
  tcase_add_test(create3, test_3);

  TCase *create4 = tcase_create("test_4\t");
  suite_add_tcase(suite, create4);
  tcase_add_test(create4, test_4);

  TCase *create5 = tcase_create("test_5\t");
  suite_add_tcase(suite, create5);
  tcase_add_test(create5, test_5);

  TCase *create6 = tcase_create("test_6\t");
  suite_add_tcase(suite, create6);
  tcase_add_test(create6, test_6);

  TCase *create7 = tcase_create("test_7\t");
  suite_add_tcase(suite, create7);
  tcase_add_test(create7, test_7);

  TCase *create8 = tcase_create("test_8\t");
  suite_add_tcase(suite, create8);
  tcase_add_test(create8, test_8);

  TCase *create9 = tcase_create("test_9\t");
  suite_add_tcase(suite, create9);
  tcase_add_test(create9, test_9);

  TCase *create10 = tcase_create("test_10\t");
  suite_add_tcase(suite, create10);
  tcase_add_test(create10, test_10);

  TCase *create11 = tcase_create("test_11\t");
  suite_add_tcase(suite, create11);
  tcase_add_test(create11, test_11);

  TCase *create12 = tcase_create("test_12\t");
  suite_add_tcase(suite, create12);
  tcase_add_test(create12, test_12);

  TCase *create13 = tcase_create("test_13\t");
  suite_add_tcase(suite, create13);
  tcase_add_test(create13, test_13);

  TCase *create14 = tcase_create("test_14\t");
  suite_add_tcase(suite, create14);
  tcase_add_test(create14, test_14);

  TCase *create15 = tcase_create("test_15\t");
  suite_add_tcase(suite, create15);
  tcase_add_test(create15, test_15);

  TCase *create16 = tcase_create("test_16\t");
  suite_add_tcase(suite, create16);
  tcase_add_test(create16, test_16);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
