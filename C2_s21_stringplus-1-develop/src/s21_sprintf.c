#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  int result = 0;
  va_list args = {0};
  va_start(args, format);
  int i = 0;
  int flagError = 1;
  int text = 0;
  int index = i;
  flags fl = {0};
  specifiers spec = {0};
  while (format[i] != '\0') {
    text = 0;
    if (format[i] == '%') text = 1;
    index = i;
    s21_memset(&fl, 0, sizeof(fl));
    fl.precision = -1;
    s21_memset(&spec, 0, sizeof(spec));
    flagError = 1;
    flagError = parser(format, &i, &args, &fl, &spec, &result, str);
    if (!flagError) i = index;
    if ((spec.E || spec.e || spec.f || spec.G || spec.g) && flagError != 0) {
      f_e_g_func(str + result, &result, &fl, args, spec);
    }
    if ((spec.d || spec.i || spec.x || spec.X || spec.o || spec.u || spec.p) &&
        flagError != 0) {
      int_func(str, &result, fl, spec, args);
    }
    if (spec.n && flagError != 0) {
      n_func(result, &args);
    }
    if (spec.c && flagError != 0) {
      c_func(str, &result, fl, &args);
    }
    if (spec.s && flagError != 0) {
      s_func(str, &result, fl, &args);
    }
    if (!text || flagError == 0) {
      str[result] = format[i];
      i++;
      result++;
    }
  }
  str[result] = '\0';
  va_end(args);
  return result;
}

void percent(int *i, char *str, int *result) {
  str[*result] = '%';
  *i += 2;
  *result += 1;
}

int checkError(int begin, int end, const char *format) {
  char *x = s21_NULL;
  int flagError = 1;
  for (int i = begin + 1; i < end; i++) {
    x = s21_strchr("-+ 0#1234567890.*lLh", format[i]);
    if (x == s21_NULL) flagError = 0;
  }
  return flagError;
}

int parser(const char *format, int *index, va_list *args, flags *fl,
           specifiers *spec, int *result, char *str) {
  int begin = *index;
  int end = *index;
  int flagError = 1;
  if (format[*index] == '%') {
    if (format[*index + 1] == '%')
      percent(index, str, result);
    else {
      flagError *= searchSpecif(&end, format, spec);
      if (flagError != 0) flagError *= checkError(begin, end, format);
      if (flagError != 0) flagError *= searchFlags(&begin, end, format, fl);
      if (flagError != 0)
        flagError *= searWidPrec(&begin, end, format, fl, args);
      if (flagError != 0)
        flagError *= searWidPrec(&begin, end, format, fl, args);
      if (flagError != 0) flagError *= searchLen(&begin, end, format, fl);
      *index = end + 1;
    }
  }
  return flagError;
}

int searchSpecif(int *index, const char *format, specifiers *spec) {
  int stopFlag = 0;
  char *x = s21_NULL;
  while (format[*index] != '\0' && stopFlag == 0) {
    x = s21_strchr("cdieEfgGosuxXpn", format[*index]);
    if (x != s21_NULL) {
      swSpecif(spec, format[*index]);
      stopFlag = 1;
    } else {
      *index += 1;
    }
  }
  if (x == s21_NULL) *index = 0;
  return *index;
}
int searchFlags(int *begin, int end, const char *format, flags *fl) {
  int stopflag = 0;
  int flagError = 1;
  char *x = s21_NULL;
  for (int i = *begin + 1; i <= end; i++) {
    x = s21_strchr("-+ 0#", format[i]);
    if (x != s21_NULL && stopflag == 0) {
      swFlags(fl, format[i]);
    }
    if (x == s21_NULL && stopflag == 0) {
      *begin = i;
      stopflag = 1;
    }
    if (x != s21_NULL && stopflag == 1 && format[i] != '0') {
      flagError = 0;
    }
  }
  return flagError;
}

int searWidPrec(int *begin, int end, const char *format, flags *fl,
                va_list *args) {
  numFlags num = {0};
  num.flagEr = 1;
  num.x = s21_NULL;
  char buffer[1024] = {'\0'};
  if (format[*begin] != '.' && fl->precision == -1) {
    for (int i = *begin; i < end && format[i] != '.'; i++) {
      if ((format[i] >= '0' && format[i] <= '9') || format[i] == '*') {
        searchStar(begin, i, &num, format, buffer, &fl->width, args);
        if (fl->width < 0) {
          fl->minus = 1;
          fl->width = -1 * fl->width;
        }
      }
    }
  } else {
    if (format[*begin] == '.') {
      num.countPoint++;
      if ((format[*begin + 1] < '0' || format[*begin + 1] > '9') &&
          format[*begin + 1] != '*') {
        if (format[*begin + 1] == '.') {
          num.countPoint++;
        }
        fl->precision = 0;
        *begin += 1;
      } else {
        if (format[*begin + 1] == '*') {
          *begin += 2;
          fl->precision = va_arg(*args, int);
        } else {
          for (int i = *begin + 1; i < end; i++) {
            searchNumber(begin, i, &num, format, buffer);
          }
          fl->precision = s21_atoi(buffer);
        }
      }
    }
  }
  if (num.countNumber > 0 && num.countStar > 0) num.flagEr = 0;
  if (num.countStar > 1 || num.countPoint > 1) num.flagEr = 0;
  return num.flagEr;
}
void searchStar(int *begin, int index, numFlags *num, const char *format,
                char *buffer, int *value, va_list *args) {
  int n = 0;
  if (format[index] == '.') {
    *begin += 1;
    num->countPoint++;
  }
  if (format[index] == '*') {
    *value = va_arg(*args, int);
    *begin += 1;
    num->countStar++;
    num->stopFl = 1;
  } else {
    searchNumber(begin, index, num, format, buffer);
    n = s21_atoi(buffer);
    *value = n;
  }
}
void searchNumber(int *begin, int index, numFlags *fl, const char *format,
                  char *buffer) {
  fl->x = s21_strchr("1234567890", format[index]);
  if (fl->x != s21_NULL) {
    *begin += 1;
    buffer[fl->size] = format[index];
    fl->size++;
    fl->countNumber++;
  }
  if (fl->x == s21_NULL && fl->stopFl == 0) {
    *begin = index;
    fl->stopFl = 1;
  }
}
int searchLen(int *begin, int end, const char *format, flags *fl) {
  int stopFlag = 0;
  int flagError = 1;
  char *x = s21_NULL;
  int count = 0;
  for (int i = *begin; i <= end && flagError == 1; i++) {
    x = s21_strchr("hlL", format[i]);
    if (x != s21_NULL) {
      *begin = i + 1;
      stopFlag = 1;
      count++;
      swFlags(fl, format[i]);
    }
    if (x == s21_NULL && stopFlag == 0) {
      *begin = i;
      stopFlag = 1;
    }
    if (x != s21_NULL && stopFlag == 1) {
      if (count > 1) flagError = 0;
    }
  }
  return flagError;
}
void swFlags(flags *fl, char ch) {
  switch (ch) {
    case '-':
      fl->minus = 1;
      break;
    case '+':
      fl->plus = 1;
      break;
    case ' ':
      fl->space = 1;
      break;
    case '#':
      fl->sharp = 1;
      break;
    case '0':
      fl->zero = 1;
      break;
    case 'h':
      fl->len_h = 1;
      break;
    case 'l':
      fl->len_l = 1;
      break;
    case 'L':
      fl->len_L = 1;
      break;
    default:
      break;
  }
}
void swSpecif(specifiers *spec, char ch) {
  switch (ch) {
    case 'c':
      spec->c = 1;
      break;
    case 'd':
      spec->d = 1;
      break;
    case 'i':
      spec->i = 1;
      break;
    case 'e':
      spec->e = 1;
      break;
    case 'E':
      spec->E = 1;
      break;
    case 'f':
      spec->f = 1;
      break;
    case 'g':
      spec->g = 1;
      break;
    case 'G':
      spec->G = 1;
      break;
    case 'o':
      spec->o = 1;
      break;
    case 's':
      spec->s = 1;
      break;
    case 'x':
      spec->x = 1;
      break;
    case 'X':
      spec->X = 1;
      break;
    case 'p':
      spec->p = 1;
      break;
    case 'n':
      spec->n = 1;
      break;
    case 'u':
      spec->u = 1;
      break;
    default:
      break;
  }
}
void copyChar(char *str, int *result, char ch) {
  str[*result] = ch;
  *result += 1;
}
void insertSpace(char *str, int *result, int count) {
  for (int i = 0; i < count; i++, *result += 1) {
    str[*result] = ' ';
  }
}
void c_func(char *str, int *result, flags fl, va_list *args) {
  if ((fl.minus && !fl.width) || (!fl.minus && !fl.width)) {
    copyChar(str, result, va_arg(*args, int));
  }
  if (!fl.minus && fl.width) {
    insertSpace(str, result, fl.width - 1);
    copyChar(str, result, va_arg(*args, int));
  }
  if (fl.minus && fl.width) {
    copyChar(str, result, va_arg(*args, int));
    insertSpace(str, result, fl.width - 1);
  }
}
void s_func(char *str, int *result, flags fl, va_list *args) {
  char copyArgs[1024] = {'\0'};
  s21_strcpy(copyArgs, va_arg(*args, char *));
  s21_size_t len = fl.precision;
  s21_size_t lenCopy = s21_strlen(copyArgs);
  int count = 0;
  if ((!fl.minus && !fl.width) || (fl.minus && !fl.width)) {
    for (s21_size_t i = 0; i < len && i < lenCopy; i++) {
      copyChar(str, result, copyArgs[i]);
    }
  }
  if (fl.minus && fl.width) {
    for (s21_size_t i = 0; i < len && i < lenCopy; i++) {
      copyChar(str, result, copyArgs[i]);
    }
    if (fl.width > (int)len) {
      if (fl.precision == 0) count = fl.width;
      if (len < lenCopy)
        count = fl.width - len;
      else
        count = fl.width - lenCopy;
      insertSpace(str, result, count);
    }
  }
  if (!fl.minus && fl.width) {
    if (fl.width >= (int)len) {
      if (fl.precision == 0) count = fl.width;
      if (len < lenCopy)
        count = fl.width - len;
      else
        count = fl.width - lenCopy;
      insertSpace(str, result, count);
    }
    for (s21_size_t i = 0; i < len && i < lenCopy; i++) {
      copyChar(str, result, copyArgs[i]);
    }
  }
}
void n_func(int result, va_list *args) {
  int *p = s21_NULL;
  p = va_arg(*args, int *);
  *p = result;
}
int f_e_g_func(char *str, int *result, flags *flag, va_list args,
               specifiers s) {
  int sign_ = 0;
  long double num = 0;
  if (flag->len_L == 1)
    num = va_arg(args, long double);
  else
    num = va_arg(args, double);
  int sdvig = 0;
  char tmp[1024] = {'\0'};
  sdvig = plus_or_space(*flag, tmp, sdvig, num);
  if (num < 0) {
    num = num * -1;
    tmp[0] = '-';
    sdvig++;
  }
  if (flag->precision == -1 && !s.g && !s.G)
    flag->precision = 6;
  else if (flag->precision == 0 && (s.G == 1 || s.g == 1))
    flag->precision = 1;
  round_9(num, *flag);
  if (s.G == 1 || s.g == 1) {
    g_func(flag, num, &s);
  }
  if (s.E == 1 || s.e == 1) sign_ = exp_func(&num);
  long double left = 0;
  long double right = modfl(num, &left);
  if ((s.G == 1 || s.g == 1) && !s.e && !s.E)
    flag->precision += significant_digits(right);
  before_dot(tmp, sdvig, left);
  after_dot(*flag, tmp, right);
  if ((s.G == 1 || s.g == 1) && !s.E && !s.e) {
    g_zero(tmp, flag->precision);
  }
  prec_nzero(*flag, tmp + sdvig);
  if (s.E == 1 || s.e == 1) {
    add_e_E(tmp, sign_, s21_strlen(tmp), s);
  }
  if (flag->width > (long int)s21_strlen(tmp)) {
    if (flag->zero == 1 && tmp[0] == '-') {
      flag->width--;
      flag_w(*flag, tmp + 1);
    } else
      flag_w(*flag, tmp);
  }
  check_res(tmp, result);
  s21_strcpy(str, tmp);
  return *result;
}

void before_dot(char *tmp, int sdvig, long double left) {
  int j = 0;
  while ((long long int)left >= LLONG_MAX || (long long int)left <= LLONG_MIN) {
    left = left / 10;
    j++;
  }
  s21_itoa((long long int)left, tmp + sdvig);
  left = left - (long long int)left;
  while (j > 0) {
    left = left * 10;
    s21_itoa((int)left, tmp + s21_strlen(tmp));
    left = left - (int)left;
    j--;
  }
}

void after_dot(flags flag, char *tmp, long double right) {
  int round = 0;
  if (flag.precision != 0) tmp[s21_strlen(tmp)] = '.';
  int i = 0;
  while (i <= flag.precision) {
    right = right * 10;
    if (i == flag.precision) {
      round = (int)right;
    } else
      s21_itoa((int)right, tmp + s21_strlen(tmp));
    right = right - (int)right;
    i++;
  }
  r_doble(tmp, round);
}

int exp_func(long double *exp) {
  int ret = 0;
  long double left = 0;
  long double right = modfl(*exp, &left);
  if (right != 0 || left != 0) {
    while (((long int)*exp == 0 || (long long int)*exp > 9)) {
      if ((long long int)*exp == 0) {
        *exp = *exp * 10;
        ret--;
      } else if ((long long int)*exp > 9) {
        *exp = *exp / 10;
        ret++;
      }
    }
  }
  return ret;
}

void add_e_E(char *str, long int sign_, s21_size_t len, specifiers s) {
  if (s.e == 1) {
    str[len] = 'e';
    len++;
  } else if (s.E == 1) {
    str[len] = 'E';
    len++;
  }
  if (sign_ >= 0) {
    str[len] = '+';
    len++;
  } else {
    str[len] = '-';
    len++;
  }
  if (sign_ >= -9 && sign_ <= 9) {
    if (sign_ < 0) sign_ = sign_ * -1;
    str[len] = 48;
    str[len + 1] = 48 + sign_;
  } else {
    s21_itoa((sign_ < 0 ? (sign_ * -1) : sign_), str + len);
  }
}

void prec_nzero(flags flag, char *tmp) {
  if (flag.precision == 0 && flag.sharp == 1) tmp[s21_strlen(tmp)] = '.';
}

int plus_or_space(flags flag, char *tmp, int sdvig, long double num) {
  if (flag.plus == 1 && num >= 0) {
    tmp[0] = '+';
    sdvig++;
  } else if (flag.space == 1 && num >= 0) {
    tmp[0] = ' ';
    sdvig++;
  }
  return sdvig;
}

void flag_w(flags f, char *str) {
  char temp[1024] = {'\0'};
  int i = 0;
  char c = ' ';
  if (f.minus != 1) {
    s21_strcpy(temp, str);
    s21_memset(str, '\0', s21_strlen(str));
    if (f.zero == 1) c = '0';
    for (; i < f.width - (int)s21_strlen(temp); i++) {
      str[i] = c;
    }
    s21_strcpy(str + s21_strlen(str), temp);
  } else {
    for (int i = s21_strlen(str); i < f.width; i++) {
      if (f.zero == 1)
        str[i] = '0';
      else
        str[i] = ' ';
    }
  }
  str[s21_strlen(str)] = '\0';
}

void r_doble(char *str, int round) {
  int i = s21_strlen(str) - 1;
  if (round >= 5) {
    str[s21_strlen(str) - 1] = str[s21_strlen(str) - 1] + 1;
    if (str[s21_strlen(str) - 2] != '.') {
      while (str[i] >= '9' && i >= 0) {
        if (str[i] >= 9) {
          str[i - 1] = str[i - 1] + 1;
          str[i] = '0';
        }
        if (str[i] == '.' || str[i] == '/') str[i] = '.';
        i--;
      }
    }
  }
}

void g_func(flags *flag, long double g, specifiers *s) {
  int sign_ = 0;
  long double tmp = g;
  sign_ = exp_func(&tmp);
  int len_of_left = 0;
  long double left = 0;
  modfl(g, &left);
  while ((int)left != 0) {
    left /= 10;
    len_of_left++;
  }
  if (sign_ < -4 || (flag->precision < len_of_left && flag->precision != -1)) {
    if (s->g) s->e = 1;
    if (s->G) s->E = 1;
    if (flag->precision == -1)
      flag->precision = 0;
    else
      flag->precision -= 1;
  } else {
    if (flag->precision == -1) flag->precision = 6;
    flag->precision -= len_of_left;
    s->f = 1;
  }
}

void g_zero(char *tmp, int precision) {
  int i = 0;
  int j = 0;
  i = s21_strlen(tmp) - 1;
  if (s21_strchr(tmp, '.') != NULL) {
    while (tmp[i] == '0') {
      tmp[i] = '\0';
      i--;
      if (tmp[i] == '.') tmp[i] = '\0';
    }
    i = s21_strlen(s21_strchr(tmp, '.')) - 1;
    j = s21_strlen(tmp);
    while (i < precision) {
      tmp[j] = 48;
      i++;
      j++;
    }
  }
}

int significant_digits(long double right) {
  double x = 0.1;
  int zeroes = 0;
  while ((right - x) < 0) {
    x /= 10;
    zeroes += 1;
  }
  return zeroes;
}

void round_9(long double num, flags flag) {
  long double temp = num - (long long int)num;
  int i = 0;
  int round = 0;
  while (i <= flag.precision) {
    temp = temp * 10;
    if (i == flag.precision) round = (int)temp;
    temp = temp - (int)temp;
    i++;
  }
  if (round == 9) num = roundl(num);
}

void check_res(char *tmp, int *res) {
  int j = 0;
  while (tmp[j] != '\0') {
    *res = *res + 1;
    j++;
  }
}

int s21_atoi(const char *str) {
  long res = 0;
  long sign = 1;
  unsigned int i = 0;
  while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
         str[i] == '\v' || str[i] == '\f')
    i++;
  if (str[i] == '-' || str[i] == '+') {
    if (str[i] == '-') sign = -1;
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9') {
    res = res * 10 + str[i] - '0';
    i++;
  }
  return ((int)(res * sign));
}

int s21_itoa(long long int n, char *str) {
  int stop = 0;
  long long int temp = n;
  int i = len_of_int(temp);
  int ret = len_of_int(temp);
  if (str != s21_NULL && stop != 1) {
    str[i] = '\0';
    i--;
    if (n == 0) {
      str[0] = '0';
      stop = 1;
    }
    if (n <= -1) {
      str[0] = '-';
      n = n * -1;
    }
    while (n > 0) {
      str[i] = 48 + (n % 10);
      n = n / 10;
      i--;
    }
  } else
    str = s21_NULL;
  return ret;
}

int len_of_int(long long int num) {
  int l = 0;
  if (num < 0) {
    num = num * -1;
    l++;
  }
  while (num > 0) {
    num = num / 10;
    l++;
  }
  return l;
}

int int_func(char *str, int *result, flags fl, specifiers spec, va_list args) {
  long d = 0;
  if (!spec.p) d = length_flag(d, fl, args);
  unsigned long u = unsigned_value(d, fl);
  int len = num_length(spec, d, u);
  char buf[len + 1];

  if (spec.p) {
    hexadecimal(p_func(&fl, args, &spec), buf, &len, spec);
  }
  flag_processing(&fl, spec, d);
  if (spec.d || spec.i) {
    int_to_str(d < 0 ? d * (-1) : d, buf);
  } else if (spec.u)
    int_to_str(u, buf);
  else if ((spec.x || spec.X) && !spec.p) {
    hexadecimal(unsigned_value(d, fl), buf, &len, spec);
  } else if (spec.o) {
    octal(unsigned_value(d, fl), buf, &len);
  }
  if (fl.space) space(str, result);
  if (!fl.minus && fl.width > len) width(str, result, fl, len);
  if (fl.plus && (spec.d || spec.i)) {
    sign(str, result, d);
  }
  if (fl.sharp && (spec.x || spec.X || spec.o) &&
      ((d != 0 && !spec.p) || spec.p))
    sharp(str, result, spec);
  if (fl.precision > len) {
    precision(str, result, fl, len, spec);
  }
  if (!fl.emp) {
    s21_strcpy(str + *result, buf);
    *result += len;
  }
  if (fl.minus && fl.width > len) {
    width(str, result, fl, len);
  }
  return 0;
}

long length_flag(long d, flags fl, va_list args) {
  if (fl.len_l)
    d = va_arg(args, long int);
  else
    d = va_arg(args, int);
  if (fl.len_h) d = (short)d;
  return d;
}

void sign(char *str, int *result, long d) {
  if (d < 0)
    str[*result] = '-';
  else
    str[*result] = '+';
  *result += 1;
}

int num_length(specifiers spec, long d, unsigned long u) {
  int len = spec.o == 1 ? MAX_OLEN : MAX_XLEN;
  if (spec.d || spec.i)
    len = d < 0 ? (len_of_i(-1 * d)) : len_of_i(d);
  else if (spec.u) {
    len = len_of_i(u);
  }
  return len;
}

void flag_processing(flags *fl, specifiers spec, long d) {
  if (spec.x || spec.X || spec.o || spec.u) {
    fl->plus = 0;
    fl->space = 0;
  }
  if (fl->minus) fl->zero = 0;
  if (spec.d || spec.i || spec.u) fl->sharp = 0;
  if (fl->precision != -1) fl->zero = 0;
  if (d < 0 && (spec.d || spec.i)) fl->plus = 1;
  if (fl->plus || spec.o || spec.u || spec.x || spec.X) fl->space = 0;
  if (fl->sharp && (spec.x || spec.X || spec.o)) {
    if (d == 0 && !spec.p)
      fl->sharp = 0;
    else if (spec.x || spec.X)
      fl->sharp = 2;
  }
  if (fl->width && fl->zero && fl->precision <= fl->width) {
    fl->precision = fl->width - fl->plus - (spec.o ? 0 : fl->sharp);
  }
  if (d == 0 && fl->precision == 0) fl->emp = 1;
}

void sharp(char *str, int *result, specifiers spec) {
  str[*result] = '0';
  *result += 1;
  if (spec.x || spec.X) {
    if (spec.x) str[*result] = 'x';
    if (spec.X) str[*result] = 'X';
    *result += 1;
  }
}
void precision(char *str, int *result, flags fl, int len, specifiers spec) {
  fl.sharp = (spec.x || spec.X) ? 0 : fl.sharp;
  for (int j = 0; j < fl.precision - len - fl.sharp; j++) {
    str[*result] = '0';
    *result += 1;
  }
}

void width(char *str, int *result, flags fl, int len) {
  if (!fl.emp)
    fl.width = fl.precision > len
                   ? fl.width - fl.precision - fl.plus - fl.sharp - fl.space
                   : fl.width - len - fl.plus - fl.sharp - fl.space;
  for (; fl.width > 0; fl.width--) {
    str[*result] = ' ';
    *result += 1;
  }
}

void space(char *str, int *result) {
  str[*result] = ' ';
  *result += 1;
}

void reverse_str(int len, char *buf) {
  char temp = ' ';
  for (int j = 0; j < len / 2; j++) {
    temp = buf[j];
    buf[j] = buf[len - 1 - j];
    buf[len - 1 - j] = temp;
  }
}

void hexadecimal(unsigned long x, char *buf, int *len, specifiers spec) {
  int i = 0;
  int tmp = 0;
  do {
    tmp = x % 16;
    if (tmp == 10)
      buf[i] = spec.x ? 'a' : 'A';
    else if (tmp == 11)
      buf[i] = spec.x ? 'b' : 'B';
    else if (tmp == 12)
      buf[i] = spec.x ? 'c' : 'C';
    else if (tmp == 13)
      buf[i] = spec.x ? 'd' : 'D';
    else if (tmp == 14)
      buf[i] = spec.x ? 'e' : 'E';
    else if (tmp == 15)
      buf[i] = spec.x ? 'f' : 'F';
    else
      buf[i] = 48 + tmp;
    x /= 16;
    i++;
  } while (x != 0);
  buf[i] = '\0';
  *len = i;
  reverse_str(*len, buf);
}

unsigned long unsigned_value(long d, flags fl) {
  unsigned long x = d;
  if (d < 0) {
    if (fl.len_l) {
      x = ULONG_MAX + d + 1;
    } else if (fl.len_h) {
      x = USHRT_MAX + d + 1;
    } else {
      x = UINT_MAX + d + 1;
    }
  }
  return x;
}
void octal(unsigned long x, char *buf, int *len) {
  int i = 0;
  do {
    buf[i] = 48 + x % 8;
    x /= 8;
    i++;
  } while (x != 0);
  buf[i] = '\0';
  *len = s21_strlen(buf);
  reverse_str(*len, buf);
}

void int_to_str(unsigned long int n, char *str) {
  int i = 0;
  unsigned long temp = n;
  int stop = 0;
  int t = i += len_of_i(temp);
  if (str != s21_NULL && stop != 1) {
    i--;
    if (n == 0) {
      str[0] = '0';
      stop = 1;
    }
    while (n > 0) {
      str[i] = 48 + (n % 10);
      n = n / 10;
      i--;
    }
    str[t] = '\0';
  } else
    str = s21_NULL;
}

int len_of_i(unsigned long int num) {
  int l = 0;
  if (num == 0) l = 1;
  while (num > 0) {
    num = num / 10;
    l++;
  }
  return l;
}

unsigned long p_func(flags *fl, va_list args, specifiers *spec) {
  unsigned long p = va_arg(args, unsigned long);
  spec->x = 1;
  fl->sharp = 1;
  fl->len_l = 1;
  return p;
}
