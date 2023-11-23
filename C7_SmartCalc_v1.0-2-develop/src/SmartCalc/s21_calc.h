#ifndef _S21_CALC_H_
#define _S21_CALC_H_

//#include <check.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  mod = 37,
  openB = 40,
  closeB,
  mul = 42,
  sum = 43,
  del = 45,
  divi = 47,
  powr = 94,
  coss = 99,
  sinn = 115,
  tann = 116,
  acoss = 67,
  asinn = 83,
  atann = 84,
  sqrtt = 113,
  lnn = 110,
  logg = 103,
  unar_pos = 124,
  unar_neg = 126
} type_sign;

typedef enum {
  // open_b,
  // close_b,
  plus_minus,
  div_mul_mod,
  expon_funs,
  // unary
} prior_t;

typedef struct st {
  int symbol;
  struct st *next;
} stack;

typedef struct num {
  long double num;
  struct num *next;
} number;

typedef struct cr {
  double per_month;
  double per_month_first;
  double per_month_last;
  double pereplata;
  double sum;
} credit;

long double s21_smart_calc(const char *str, long double *res, long double x);

int polish(char *str, char **out);
void push(stack **st, int symbol);
int del_peak(stack **st);
int cut_num(char *str, char *out, int *i);
int digits(char c);
int is_func(int *i, char *str);
void move_to_out(stack **st, char **out);
// int is_empty(stack *st);
int is_oper(char c);
int is_unary(char *str, int *i);
int get_prior(int sign);

//=====//

int calc(char *str, long double *res);
long double del_peak_num(number **st);
void push_num(number **st, long double num);
long double operation(long double right, long double left, int oper);
int is_short_fun(char c);
long double funstion(long double peak, int oper, long double *num);
int count_(char *str, char c);

//----//
credit s21_credit(double sum, int month, double percent, int type_c);

#endif  // SMART_CALC
