#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define s21_PI 3.14159265358979323846
#define s21_M_PI_2 1.57079632679489661923
#define s21_M2_PI 0.636619772367581343076
#define s21_e 2.7182818284590452353602874
#define s21_INF 1.0 / 0.0
#define s21_EPS 1e-9
#define s21_DBL_MAX 1.7976931348623158e+308
#define s21_NAN 0.0 / 0.0
#define s21_M_LN10 2.30258509299404568402

// вычисляет абсолютное значение целого числа
int s21_abs(int x);

// вычисляет арккосинус
long double s21_acos(double x);

// вычисляет арксинус
long double s21_asin(double x);

// вычисляет арктангенс
long double s21_atan(double x);

// возвращает ближайшее целое число, не меньшее заданного значения
long double s21_ceil(double x);

// вычисляет косинус
long double s21_cos(double x);

// возвращает значение e, возведенное в заданную степень
long double s21_exp(double x);

// вычисляет абсолютное значение числа с плавающей точкой
long double s21_fabs(double x);

// возвращает ближайшее целое число, не превышающее заданное значение
long double s21_floor(double x);

// остаток операции деления с плавающей точкой
long double s21_fmod(double x, double y);

// вычисляет натуральный логарифм
long double s21_log(double x);

// возводит число в заданную степень
long double s21_pow(double base, double exp);

// вычисляет синус
long double s21_sin(double x);

// вычисляет квадратный корень
long double s21_sqrt(double x);

// вычисляет тангенс
long double s21_tan(double x);

// вычисляет факториал
long double s21_fact(double x);

// поиск Cos/Sin
long double searchCosSin(double x, int n);

#endif  // SRC_S21_MATH_H_
