#include <check.h>

#include "backend.h"

START_TEST(s21_3Dviever_test_1) {
  int numVer = 24;
  int numFac = 88;
  char fileName[] = "test.obj";
  data_struct myData = {0};
  readOne(fileName, &myData);
  readTwo(fileName, &myData);
  ck_assert_int_eq(myData.countVertex, numVer);
  ck_assert_int_eq(myData.countFacets, numFac);
  ck_assert_double_eq(myData.vector_3d[0], 1);
  ck_assert_double_eq(myData.vector_3d[myData.countVertex - 1], 2);
  centerVertex(&myData);
  ck_assert_double_eq(myData.vector_3d[0], -3.5);
  ck_assert_double_eq(myData.vector_3d[1], -2);
  ck_assert_double_eq(myData.vector_3d[2], 1.5);
  changeScale(&myData, 0.3);
  ck_assert_double_eq_tol(myData.vector_3d[0], 0.66667, 6);
  ck_assert_double_eq_tol(myData.vector_3d[1], 0.266667, 6);
  ck_assert_double_eq_tol(myData.vector_3d[2], 0.2, 6);
  cleanAll(&myData);
}
END_TEST

START_TEST(s21_3Dviever_test_2) {
  int numVer = 13320;
  int numFac = 35262;
  char fileName[] = "lamp.obj";
  data_struct myData = {0};
  readOne(fileName, &myData);
  readTwo(fileName, &myData);
  ck_assert_int_eq(myData.countVertex, numVer);
  ck_assert_int_eq(myData.countFacets, numFac);
  ck_assert_double_eq(myData.vector_3d[0], 0);
  ck_assert_double_eq(myData.vector_3d[myData.countVertex - 1], -0.000012);
  centerVertex(&myData);
  ck_assert_double_eq_tol(myData.vector_3d[0], -0.468015, 6);
  ck_assert_double_eq_tol(myData.vector_3d[1], 5.84556, 6);
  ck_assert_double_eq_tol(myData.vector_3d[2], 1.5, 6);
  changeScale(&myData, 0.3);
  ck_assert_double_eq_tol(myData.vector_3d[0], 0.66667, 6);
  ck_assert_double_eq_tol(myData.vector_3d[1], 0.266667, 6);
  ck_assert_double_eq_tol(myData.vector_3d[2], 0.2, 6);
  cleanAll(&myData);
}
END_TEST

START_TEST(s21_3Dviever_test_3) {
  int numVer = 24;
  int numFac = 60;
  char fileName[] = "cube.obj";
  data_struct myData = {0};
  readOne(fileName, &myData);
  readTwo(fileName, &myData);
  ck_assert_int_eq(myData.countVertex, numVer);
  ck_assert_int_eq(myData.countFacets, numFac);
  ck_assert_double_eq(myData.vector_3d[0], 0);
  ck_assert_double_eq(myData.vector_3d[myData.countVertex - 1], 2);
  centerVertex(&myData);
  ck_assert_double_eq(myData.vector_3d[0], -1);
  ck_assert_double_eq(myData.vector_3d[1], -1);
  ck_assert_double_eq(myData.vector_3d[2], -1);
  changeScale(&myData, 0.3);
  ck_assert_double_eq_tol(myData.vector_3d[0], 0.66667, 6);
  ck_assert_double_eq_tol(myData.vector_3d[1], 0.266667, 6);
  ck_assert_double_eq_tol(myData.vector_3d[2], 0.2, 6);
  cleanAll(&myData);
}
END_TEST

START_TEST(s21_3Dviever_test_4) {
  data_struct data = {0};
  data.countVertex = 12;
  data.vector_3d = calloc(data.countVertex, sizeof(double));

  data.vector_3d[0] = -4;
  data.vector_3d[1] = -1;
  data.vector_3d[2] = 0;
  data.vector_3d[3] = -4;
  data.vector_3d[4] = 1;
  data.vector_3d[5] = 0;
  data.vector_3d[6] = 4;
  data.vector_3d[7] = 1;
  data.vector_3d[8] = 0;
  data.vector_3d[9] = 4;
  data.vector_3d[10] = -1;
  data.vector_3d[11] = 0;
  double ang = 0;
  ang = 90.0 / 180.0 * 3.1415926535;
  rote_Z(&data, ang);
  ck_assert_ldouble_eq_tol(data.vector_3d[0], 1.00, 2);
  ck_assert_ldouble_eq_tol(data.vector_3d[1], -4.0, 2);
  ck_assert_double_eq(data.vector_3d[2], 0.0);
  ck_assert_double_eq_tol(data.vector_3d[3], -1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[4], -4.00, 2);
  ck_assert_double_eq(data.vector_3d[5], 0);
  ck_assert_double_eq_tol(data.vector_3d[6], -1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[7], 4.00, 2);
  ck_assert_double_eq(data.vector_3d[8], 0);
  ck_assert_double_eq_tol(data.vector_3d[9], 1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[10], 4.00, 2);
  ck_assert_double_eq(data.vector_3d[11], 0);

  free(data.vector_3d);
}
END_TEST

START_TEST(s21_3Dviever_test_5) {
  data_struct data = {0};
  data.countVertex = 12;
  data.vector_3d = calloc(data.countVertex, sizeof(double));

  data.vector_3d[2] = -4;
  data.vector_3d[1] = -1;
  data.vector_3d[0] = 0;
  data.vector_3d[5] = -4;
  data.vector_3d[4] = 1;
  data.vector_3d[3] = 0;
  data.vector_3d[8] = 4;
  data.vector_3d[7] = 1;
  data.vector_3d[6] = 0;
  data.vector_3d[11] = 4;
  data.vector_3d[10] = -1;
  data.vector_3d[9] = 0;
  double ang = 0;
  ang = 90.0 / 180.0 * 3.1415926535;
  rote_X(&data, ang);
  ck_assert_ldouble_eq_tol(data.vector_3d[0], 0.00, 2);
  ck_assert_ldouble_eq_tol(data.vector_3d[1], 4.0, 2);
  ck_assert_double_eq_tol(data.vector_3d[2], -1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[3], 0.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[4], 4.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[5], 1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[6], 0, 2);
  ck_assert_double_eq_tol(data.vector_3d[7], -4.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[8], 1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[9], 0.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[10], -4.0, 2);
  ck_assert_double_eq_tol(data.vector_3d[11], -1.00, 2);

  free(data.vector_3d);
}
END_TEST

START_TEST(s21_3Dviever_test_6) {
  data_struct data = {0};
  data.countVertex = 12;
  data.vector_3d = calloc(data.countVertex, sizeof(double));

  data.vector_3d[1] = 0;
  data.vector_3d[0] = -1;
  data.vector_3d[2] = -4;

  data.vector_3d[4] = 0;
  data.vector_3d[3] = 1;
  data.vector_3d[5] = -4;

  data.vector_3d[7] = 0;
  data.vector_3d[6] = 1;
  data.vector_3d[8] = 4;

  data.vector_3d[10] = 0;
  data.vector_3d[9] = -1;
  data.vector_3d[11] = 4;

  double ang = 0;
  ang = 90.0 / 180.0 * 3.1415926535;
  rote_Y(&data, ang);
  ck_assert_ldouble_eq_tol(data.vector_3d[0], 4.00, 2);
  ck_assert_ldouble_eq_tol(data.vector_3d[1], 0.0, 2);
  ck_assert_double_eq_tol(data.vector_3d[2], -1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[3], 4.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[4], 0.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[5], 1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[6], -4, 2);
  ck_assert_double_eq_tol(data.vector_3d[7], 0.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[8], 1.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[9], -4.00, 2);
  ck_assert_double_eq_tol(data.vector_3d[10], 0.0, 2);
  ck_assert_double_eq_tol(data.vector_3d[11], -1.00, 2);

  free(data.vector_3d);
}
END_TEST

START_TEST(s21_3Dviever_test_7) {
  char fileName[] = " ";
  data_struct myData = {0};
  ck_assert_int_eq(-1, readOne(fileName, &myData));
  readTwo(fileName, &myData);
}
END_TEST

// Функция создания набора тестов.

Suite *s21_3Dviever_suite() {
  Suite *suite;

  suite = suite_create("s21_3Dviever");
  TCase *tcase_core = tcase_create("Core");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_3Dviever_test_1);
  tcase_add_test(tcase_core, s21_3Dviever_test_2);
  tcase_add_test(tcase_core, s21_3Dviever_test_3);
  tcase_add_test(tcase_core, s21_3Dviever_test_4);
  tcase_add_test(tcase_core, s21_3Dviever_test_5);
  tcase_add_test(tcase_core, s21_3Dviever_test_6);
  tcase_add_test(tcase_core, s21_3Dviever_test_7);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main() {
  Suite *suite = s21_3Dviever_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);

  // Получаем количество проваленных тестов.

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  // Сигнализируем о том, что тестирование прошло неудачно.

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
