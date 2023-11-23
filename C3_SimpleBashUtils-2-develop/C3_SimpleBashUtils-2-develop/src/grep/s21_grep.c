#include "s21_grep.h"

int main(int ac, char **av) {
  int count_files[ac];

  char *buf[1024] = {0};

  int flg = check_flags(ac, av, &flag, buf);

  if (ac <= 2 || flg == -1)
    printf(
        "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
        "[-C[num]]");
  if (flg == -3) printf("grep: option requires an argument -- e");

  get_pattern(av, ac, buf, &flag);
  int d = 0;
  while (buf[d] != NULL) d++;

  int c_files = get_file(av, ac, count_files);
  for (int i = 0; i < c_files; i++) {
    if (read_file(av[count_files[i]], buf, &flag, c_files) == 0 || flg == -2) {
      if (flag.s != 1)
        fprintf(stderr, "grep: %s: No such file or directory\n",
                av[count_files[i]]);
    }
  }

  for (int i = 0; i < d; i++) free(buf[i]);
  return 0;
}

int check_flags(int ac, char **av, FLAGS *flag, char **buf) {
  int _ind_pattern = 0;
  int flag_ = 0;
  int i = 1;
  while (i < ac) {
    if (av[i][0] == '-') {
      int j = 1;
      while (av[i][j] != '\0' && flag_ > -1) {
        switch (av[i][j]) {
          case 'f':
            flag->f = 1;
            flag_ = get_pattern_for_ef(av, buf, _ind_pattern, i, j);
            flag_ = flag_f(buf, _ind_pattern);
            flag_++;
            break;
          case 'e':
            flag->e = 1;
            flag_ = get_pattern_for_ef(av, buf, _ind_pattern, i, j);
            flag_++;
            _ind_pattern++;
            break;
          case 'i':
            flag->i = 1;
            flag_++;
            break;
          case 'v':
            flag->v = 1;
            flag_++;
            break;
          case 'c':
            flag->c = 1;
            flag_++;
            break;
          case 'l':
            flag->l = 1;
            flag_++;
            break;
          case 'n':
            flag->n = 1;
            flag_++;
            break;
          case 'h':
            flag->h = 1;
            flag_++;
            break;
          case 's':
            flag->s = 1;
            flag_++;
            break;
          case 'o':
            flag->o = 1;
            flag_++;
            break;
          default:
            flag_ = -1;
            break;
        }
        j++;
      }
      memset(av[i], '\0', strlen(av[i]));
    }
    i++;
  }
  return flag_;
}
int get_pattern_for_ef(char **av, char **buf, int _ind_pattern, int i, int j) {
  int flag = 0;
  if (av[i][j + 1] != '\0') {
    buf[_ind_pattern] = (char *)malloc(sizeof(char) * (strlen(av[i]) + 1));
    if (buf[_ind_pattern] != NULL) {
      strcpy(buf[_ind_pattern], av[i]);
      memset(av[i], '\0', strlen(av[i]));
      read_for_e_f(buf[_ind_pattern], j);
    } else
      flag = -1;
  } else if (av[i + 1] != NULL) {
    buf[_ind_pattern] = (char *)malloc(sizeof(char) * (strlen(av[i + 1]) + 1));
    if (buf[_ind_pattern] != NULL) {
      strcpy(buf[_ind_pattern], av[i + 1]);
      memset(av[i + 1], '\0', strlen(av[i + 1]));
    } else
      flag = -1;
  } else
    flag = -3;
  return flag;
}

void read_for_e_f(char *buf, int c) {
  if (strlen(buf) - c > 0) {
    char temp[strlen(buf) - c];
    int j = 0;
    for (int i = c + 1; buf[i] != '\0'; i++) {
      temp[j] = buf[i];
      j++;
    }
    temp[j] = '\0';
    strcpy(buf, temp);
  }
}
void get_pattern(char **av, int ac, char **buf, FLAGS *flag) {
  if (flag->e != 1 && flag->f != 1) {
    int i = 1;
    while (i < ac) {
      if (av[i][0] != '\0') {
        buf[0] = (char *)malloc(sizeof(char) * (strlen(av[i]) + 1));
        strcpy(buf[0], av[i]);
        memset(av[i], '\0', strlen(av[i]));
        break;
      }
      i++;
    }
  }
}
int get_file(char **av, int ac, int *count_f) {
  int j = 0;
  for (int i = 1; i < ac; i++) {
    if (av[i][0] != '\0') {
      count_f[j] = i;
      j++;
    }
  }
  count_f[j] = 0;
  return j;
}

int read_file(char *name_file, char **search, FLAGS *flag, int d) {
  int flag_match = 0;
  int flag_stop = 1;
  int flag_c = 0;
  char *str = NULL;

  size_t len = 0;
  FILE *fp;

  fp = fopen(name_file, "r");
  if (fp != NULL) {
    int i = 1;
    while (getline(&str, &len, fp) != -1) {
      regmatch_t pmatch[1] = {0};
      if (len == 0) break;
      int curr_pat = 0;
      flag_match = 0;
      int flag_for_line = 0;
      while (search[curr_pat] != NULL) {
        int res = grep(str, search[curr_pat], flag, &flag_match, flag_for_line,
                       name_file, d, i, pmatch);
        if (res > 0) flag_for_line++;
        curr_pat++;
      }
      if (flag->v == 1) v_flag(&flag_match);
      if (flag_match != 0) {
        flag_c++;
        if (flag->c != 1 && flag->l != 1 && flag_match != 0)
          output(str, flag, name_file, i, d);
      }
      i++;
    }
    if (flag->c == 1 || flag->l == 1) out_for_c_l_(flag, d, flag_c, name_file);
    fclose(fp);
  } else {
    flag_stop = 0;
  }

  free(str);
  return flag_stop;
}
void v_flag(int *match) {
  if (*match == 0)
    *match = 1;
  else
    *match = 0;
}

int grep(char *str, char *pattern, FLAGS *flag, int *match_no, int first_line,
         char *name_file, int n_files, int line, regmatch_t pmatch[1]) {
  int reg = 0;
  regex_t reegex;
  if (strcmp(pattern, ".") == 0)
    reg = regcomp(&reegex, pattern, REG_NEWLINE);
  else {
    reg = regcomp(&reegex, pattern,
                  (flag->i == 1 ? REG_ICASE | REG_EXTENDED : REG_EXTENDED));
  }
  if (reg == 0) {
    if (flag->o == 1 && flag->v != 1 && flag->c != 1 && flag->l != 1) {
      if (n_files > 1 && flag->h != 1 &&
          regexec(&reegex, str, 1, pmatch, 0) == 0)
        fprintf(stdout, "%s:", name_file);
      if (flag->n == 1 && first_line == 0 &&
          regexec(&reegex, str, 1, pmatch, 0) == 0)
        fprintf(stdout, "%d:", line);
      while (!regexec(&reegex, str, 1, pmatch, 0)) {
        if (flag->v != 1) {
          printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                 str + pmatch[0].rm_so);
          memset(str, ' ', pmatch[0].rm_eo);
          first_line++;
        }
      }
    } else {
      if (regexec(&reegex, str, 0, NULL, 0) == 0) {
        *match_no = 1;
      }
    }
    regfree(&reegex);
  }
  return first_line;
}
void output(char *str, FLAGS *flag, char *name_file, int i, int c_files) {
  if (flag->h != 1 && c_files > 1) fprintf(stdout, "%s:", name_file);
  if (flag->n == 1) fprintf(stdout, "%d:", i);
  fprintf(stdout, "%s", str);
  if (strstr(str, "\n") == NULL) fprintf(stdout, "\n");
}
void out_for_c_l_(FLAGS *flag, int c_files, int matches, char *name_file) {
  if (c_files > 1 && flag->c == 1 && flag->h != 1)
    fprintf(stdout, "%s:", name_file);
  if (flag->c == 1 && flag->l == 1 && matches > 0) matches = 1;
  if (flag->c == 1) fprintf(stdout, "%d\n", matches);
  if (flag->l == 1 && matches > 0) fprintf(stdout, "%s\n", name_file);
}

int flag_f(char **buf, int _ind_) {
  int err = 1;
  char *temp = NULL;
  size_t len = 0;
  FILE *fp;
  fp = fopen(buf[_ind_], "r");
  if (fp != NULL) {
    free(buf[_ind_]);
    while (getline(&temp, &len, fp) != -1) {
      buf[_ind_] = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
      if (buf[_ind_] != NULL) {
        strcpy(buf[_ind_], temp);
        int _len = strlen(buf[_ind_]);
        if (buf[_ind_][_len - 1] == '\n' && strlen(buf[_ind_]) > 1)
          buf[_ind_][_len - 1] = '\0';
        _ind_++;
      }
    }
    fclose(fp);
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", buf[_ind_]);
    err = -2;
  }

  free(temp);
  return err;
}
