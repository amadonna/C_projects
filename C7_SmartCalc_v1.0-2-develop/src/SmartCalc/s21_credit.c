#include "s21_calc.h"

// int main() {
//    credit cr = {0};
//    cr = s21_credit(999900, 15*12, 84*0.01, 1);
//    printf("per_m_first = %lf......per_m_last = %lf\tperpel = %lf\tsum =
//    %lf\n", cr.per_month_first, cr.per_month_last, cr.pereplata,cr.sum);
//    return 0;
// }

credit s21_credit(double sum, int month, double percent, int type_c) {
  credit cr = {0};
  double per_m = 0;
  if (sum && month && percent) {
    if (type_c == 0) {
      // double stavka = 0;
      percent /= 12;
      // printf("sum = %lf\n", 100*((0.99/12*pow((1+0.99/12),12)) / (pow((1 +
      // 0.99/12), 12) - 1)));
      cr.per_month = sum * ((percent * pow((1 + percent), month)) /
                            (pow((1 + percent), month) - 1));
      cr.pereplata = cr.per_month * month - sum;
      cr.sum = sum + cr.pereplata;
      // printf("per_m_first = %lf......per_m_last = %lf\tperpel = %lf\tsum =
      // %lf\n", cr.per_month, cr.per_month_last, cr.pereplata,cr.sum);
    } else {
      per_m = sum / month;
      for (int i = 0; i < month; i++) {
        cr.per_month = (sum - (per_m * i)) * percent / 12 + per_m;
        cr.sum += cr.per_month;
      }
      cr.per_month_first = sum * percent / 12 + per_m;
      cr.per_month_last = (sum - (per_m * (month - 1))) * percent / 12 + per_m;
      cr.pereplata = cr.sum - sum;
    }
  }
  return cr;
}
