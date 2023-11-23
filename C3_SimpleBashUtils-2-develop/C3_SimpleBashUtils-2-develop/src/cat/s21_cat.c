

#include "s21_cat.h"

int main(int ac, char** av) {
  char _c = 0;
  check_flag(ac, av, &options);
  if (ac == 1) {
    while (1) {
      fprintf(stdout, "%c", fgetc(stdin));
    }
  } else {
    int count = optind;
    while (count < ac) {
      if (ac != count) {
        read_file(av[count], _c, av[0]);
      }
      count++;
    }
  }
  return 0;
}
void read_file(char* name_file, char ch, char* command) {
  char _1_before = 0;
  char _2_before = 0;
  int for_b = 1;
  int for_n = 1;
  int ret;
  FILE* fp;
  fp = fopen(name_file, "r");
  if (fp == NULL) {
    fprintf(stderr, "%s: %s: No such file or directory\n", command, name_file);
  } else {
    int i = 0;
    while ((ch = fgetc(fp)) != EOF) {
      ret = output(ch, &options, i, for_n, for_b, _1_before, _2_before);
      if ((_1_before == '\n' || i == 0) && ch != '\n') for_b++;
      if (ret == 0 && ch == '\n') for_n++;
      _2_before = _1_before;
      _1_before = ch;
      i++;
    }
    fclose(fp);
  }
}

int output(char _ch, opt* opts, int i, int flg_n, int flg_b, char _1_before,
           char _2_before) {
  int check_empty = 0;
  int s_c = 0;
  if (opts->s == 1 && _1_before == '\n' && _2_before == '\n' && _ch == '\n') {
    check_empty++;
    s_c = 1;
  } else
    s_c = 0;
  if (opts->b == 1 && (_1_before == '\n' || i == 0) && _ch != '\n' &&
      s_c == 0) {
    printf("%6d\t", flg_b);
  } else if (opts->n == 1 && opts->b != 1 && (_1_before == '\n' || i == 0) &&
             s_c == 0) {
    printf("%6d\t", flg_n);
  }
  if (opts->e == 1 && _ch == '\n' && s_c == 0) {
    printf("$");
  }
  if (opts->t == 1 && _ch == '\t' && s_c == 0) {
    _ch = 'I';
    printf("^");
  }

  if (opts->v == 1 && s_c == 0) {
    if ((_ch >= 0 && _ch < 9) || (_ch > 10 && _ch < 32)) {
      _ch = _ch + 64;
      printf("^");
    } else if (_ch == 127) {
      _ch = '?';
      printf("^");
    }
  }
  // printf("%c", _1_before);
  if (check_empty == 0) printf("%c", _ch);
  return s_c;
}
int check_flag(int ac, char** av, opt* opts) {
  int f = 1;
  static struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                         {"squeeze-blank", 0, NULL, 's'},
                                         {"number", 0, NULL, 'n'},
                                         {NULL, 0, NULL, 0}};
  int opt;
  while ((opt = getopt_long(ac, av, "+benstvTE", long_options, NULL)) != -1) {
    switch (opt) {
      case 'b':
        opts->b = 1;
        f++;
        break;
      case 'n':
        opts->n = 1;
        f++;
        break;
      case 'e':
        opts->e = 1;
        opts->v = 1;
        f++;
        break;
      case 't':
        opts->t = 1;
        opts->v = 1;
        f++;
        break;
      case 's':
        opts->s = 1;
        f++;
        break;
      case 'v':
        opts->v = 1;
        f++;
        break;
      case 'T':
        opts->t = 1;
        f++;
        break;
      case 'E':
        opts->e = 1;
        f++;
        break;
      default:
        fprintf(stderr, "usage: %s [-benstuv] [file ...]", av[0]);
    }
  }
  return f;
}
