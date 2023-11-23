#include "s21_calc.h"

// int main(){
// // int ret = 0;
//   long double num = 0;
//   double h = 0.05;
//   long double x = -10.0;
//   for( ; x <= 10; x += h){
//     s21_smart_calc("x*x*x*x*x", &num, x);
//     //printf("\ndoubl = num = %Lf\tret = %d", num, ret);
//   }
//   return 0;
// }

long double s21_smart_calc(const char *str, long double *res, long double x) {
  char *ttt = calloc(300, sizeof(char));
  char *out = calloc(300, sizeof(char));
  int ret = 0;
  if (ttt != NULL) {
    int i = 0;
    int j = 0;
    while (str[i] != '\0') {
      if (str[i] == 'x') {
        j += sprintf(ttt + j, "(%Lg)", x);
        i++;
      }
      ttt[j] = str[i];
      i++;
      j++;
    }
  }
  // printf("input = %s\n", ttt);
  if (out != NULL) {
    if ((ret = polish(ttt, &out)) == 0) {
      // printf("out = %s\n", out);
      ret = calc(out, res);
    }
  }
  free(out);
  free(ttt);
  return ret;
}

// void replace_x(const char *str, char **out, long double x) {
//   int i = 0;
//   int j = 0;
//   while (str[i] != '\0') {
//     *out[j] = str[i];
//     printf("%c\n", *out[i]);

//     // if(str[i] == 'x') {
//     //   printf("%Lf\n", x);
//     //   //j += sprintf(*out + j, "%Lg", x);
//     //   i++;
//     // }
//     // *out[j] = str[i];
//     // //printf("%c\n", str[i]);
//     // i++;
//     j++;
//     i++;
//   }
// }

int calc(char *str, long double *res) {
  long double t = 0;
  int ret = 0;
  number *num = NULL;
  int i = 0;
  char *temp = NULL;
  ////printf("res = %s\n", str);
  while (str[i] != '\0' && ret == 0) {
    long double num_temp = 0;
    if (isspace(str[i])) i++;
    if (digits(str[i])) {
      t = 0;
      temp = calloc(20, sizeof(char));
      cut_num(str, temp, &i);
      sscanf(temp, "%Lg", &t);
      // //printf("temp = %s\n", temp);
      // //printf("///temp = %f\n", atof(temp));
      push_num(&num, t);
      free(temp);
    } else if (str[i] == '~') {
      num_temp = del_peak_num(&num) * -1;
      //////printf("num_temp = %lf\n", num_temp);
      push_num(&num, num_temp);
      i++;
    } else if (is_oper(str[i]) != 0) {
      if (num != NULL && num->next != NULL) {
        long double a = del_peak_num(&num);
        long double b = del_peak_num(&num);
        num_temp = operation(a, b, str[i]);
        push_num(&num, num_temp);
      } else
        ret = -1;
      i++;
    } else if (is_short_fun(str[i])) {
      if ((ret = funstion(del_peak_num(&num), str[i], &num_temp)) == 0)
        push_num(&num, num_temp);
      i++;
    }
    // if(num_temp == NAN || num_temp == -NAN)
    //   ret = -1;
    else
      i++;
  }

  if (num != NULL) {
    if (num != NULL && num->next == NULL)
      *res = del_peak_num(&num);
    else
      ret = -1;
  } else
    ret = -1;
  return ret;
}

long double operation(long double right, long double left, int oper) {
  long double num = 0;
  if (oper == '+')
    num = left + right;
  else if (oper == '-')
    num = left - right;
  else if (oper == '*')
    num = left * right;
  else if (oper == '/')
    num = left / right;
  else if (oper == '%')
    num = fmodl(left, right);
  else if (oper == '^')
    num = powl(left, right);
  // printf("after_oper\t%Lf %c %Lf = %Lf\n", left, oper, right, num);
  return num;
}

int is_short_fun(char c) {
  return (c == 'c' || c == 's' || c == 't' || c == 'C' || c == 'S' ||
          c == 'T' || c == 'q' || c == 'n' || c == 'g');
}

long double funstion(long double peak, int oper, long double *num) {
  // long double num = 0;
  int ret = 0;
  if (oper == 'c')
    *num = cos(peak);
  else if (oper == 's')
    *num = sin(peak);
  else if (oper == 't')
    *num = tan(peak);
  else if (oper == 'C')
    *num = acos(peak);
  else if (oper == 'S')
    *num = asin(peak);
  else if (oper == 'T')
    *num = atan(peak);
  else if (oper == 'q')
    *num = sqrt(peak);
  else if (oper == 'n')
    *num = log(peak);
  else if (oper == 'g')
    *num = log10(peak);
  //////printf("after_oper\t%c(%lf) = %lf\n", oper, peak, num);
  if (isnan(*num)) ret = -1;
  return ret;
}

void push_num(number **st, long double num) {
  number *temp = NULL;
  if ((temp = calloc(1, sizeof(number))) != NULL) {
    temp->num = num;
    temp->next = *st;
    *st = temp;
  }
}

long double del_peak_num(number **st) {
  long double ret = -1;
  number *temp = NULL;
  if (*st != NULL) {
    temp = *st;
    ret = temp->num;
    *st = (*st)->next;
    free(temp);
  }
  return ret;
}

//  ====    =====   ///

int polish(char *str, char **out) {
  int ret = 0;
  int i = 0;
  int check_func = 0;
  int check_unar = 0;
  stack *st = NULL;
  if (count_(str, '(') - count_(str, ')') != 0) ret = -1;
  while (str[i] != '\0' && ret == 0) {
    if (digits(str[i]))
      cut_num(str, *out + strlen(*out), &i);
    else if ((check_func = is_func(&i, str)) != 0) {
      push(&st, check_func);
    } else if (str[i] == '(') {
      push(&st, str[i]);
      i++;
    } else if ((check_unar = is_unary(str, &i)) != 0)
      push(&st, check_unar);
    else if (is_oper(str[i]) != 0) {
      while (st != NULL && get_prior(st->symbol) > get_prior(str[i]))
        move_to_out(&st, out);
      push(&st, str[i]);
      i++;
    } else if (str[i] == ')') {
      while (st != NULL && st->symbol != '(' && ret == 0) move_to_out(&st, out);
      if (st != NULL && st->symbol == '(') del_peak(&st);
      if (st != NULL && is_short_fun(st->symbol)) move_to_out(&st, out);
      i++;
    } else
      i++;
  }
  if (st != NULL && st->symbol == ')')
    ret = -1;
  else {
    while (st != NULL) move_to_out(&st, out);
  }
  return ret;
}

int is_unary(char *str, int *i) {
  int ret = 0;
  if (str[*i - 1] != ')' && !digits(str[*i - 1])) {
    if (str[*i] == '-')
      ret = '~';
    else if (str[*i] == '+')
      ret = '|';
  }
  if (ret != 0) *i += 1;
  return ret;
}

int get_prior(int sign) {
  int ret = 0;
  // if (sign == unar_pos || sign == unar_neg)
  //   ret = unary;
  // else if (sign == openB)
  //   ret = open_b;
  // else if (sign == closeB)
  //   ret = close_b;
  if (sign == sum || sign == del)
    ret = plus_minus;
  else if (sign == divi || sign == mul || sign == mod)
    ret = div_mul_mod;
  else if (sign >= 94 && sign <= 103)
    ret = expon_funs;
  return ret;
}

void move_to_out(stack **st, char **out) {
  char *temp = calloc(3, sizeof(char));
  if (temp != NULL) {
    temp[0] = del_peak(st);
    temp[1] = ' ';
    strcpy(*out + strlen(*out), temp);
  }
  free(temp);
}

// int is_empty(stack *st) { return (st == NULL); }

void push(stack **st, int symbol) {
  stack *temp = NULL;
  if ((temp = calloc(1, sizeof(stack))) != NULL) {
    temp->symbol = symbol;
    temp->next = *st;
    *st = temp;
  }
}

int del_peak(stack **st) {
  int ret = -1;
  stack *temp = NULL;
  if (*st != NULL) {
    temp = *st;
    ret = temp->symbol;
    *st = (*st)->next;
    free(temp);
  }
  return ret;
}

int is_oper(char c) {
  int ret = 0;
  if (c == '+' || c == '-' || c == '/' || c == '*' || c == '%' || c == '^')
    ret = c;
  return ret;
}

int cut_num(char *str, char *out, int *i) {
  int ret = 0;
  while ((str[*i] != '\0' && digits(str[*i])) ||
         (str[*i] == '.' && digits(str[*i + 1]) && digits(str[*i - 1]))) {
    out[strlen(out)] = str[*i];
    *i += 1;
  }
  if (str[*i] == 'e' || str[*i] == 'E') {
    out[strlen(out)] = str[*i];
    *i += 1;
    if (str[*i] == '+' || str[*i] == '-') {
      out[strlen(out)] = str[*i];
      *i += 1;
    }
  }
  while (str[*i] != '\0' && digits(str[*i])) {
    out[strlen(out)] = str[*i];
    *i += 1;
    ret++;
  }
  out[strlen(out)] = ' ';
  return ret;
}

int digits(char c) { return (c >= '0' && c <= '9'); }

int is_func(int *i, char *str) {
  int ret = 0;
  if (str[*i] >= 'a' && str[*i] <= 'z') {
    if (strncmp("cos", str + *i, 3) == 0)
      ret = coss;
    else if (strncmp("sin", str + *i, 3) == 0)
      ret = sinn;
    else if (strncmp("tan", str + *i, 3) == 0)
      ret = tann;
    else if (strncmp("acos", str + *i, 4) == 0)
      ret = acoss;
    else if (strncmp("asin", str + *i, 4) == 0)
      ret = asinn;
    else if (strncmp("atan", str + *i, 4) == 0)
      ret = atann;
    else if (strncmp("sqrt", str + *i, 4) == 0)
      ret = sqrtt;
    else if (strncmp("ln", str + *i, 2) == 0)
      ret = lnn;
    else if (strncmp("log", str + *i, 3) == 0)
      ret = logg;
  }
  ////printf("fun = %c\n", ret);
  if (ret == tann || ret == sinn || ret == coss || ret == logg)
    *i += 3;
  else if (ret == acoss || ret == asinn || ret == atann || ret == sqrtt)
    *i += 4;
  else if (ret == lnn)
    *i += 2;
  return ret;
}

int count_(char *str, char c) {
  int ret = 0;
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == c) ret++;
    i++;
  }
  return ret;
}
