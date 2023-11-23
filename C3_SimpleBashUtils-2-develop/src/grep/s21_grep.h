#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int t;
  int f;
  int o;
} FLAGS;
FLAGS flag = {0};
int check_flags(int ac, char **av, FLAGS *flag, char **buf);
int get_pattern_for_ef(char **av, char **buf, int _ind_pattern, int i, int j);
int other_flags(char **av, int i, FLAGS *flag);
void read_for_e_f(char *buf, int c);
void get_pattern(char **av, int ac, char **buf, FLAGS *flag);
int get_file(char **av, int ac, int *count_f);
int grep(char *str, char *pattern, FLAGS *flag, int *match_no, int first_line,
         char *name_file, int n_files, int line, regmatch_t pmatch[1]);
int read_file(char *name_file, char **search, FLAGS *flag, int d);
void output(char *str, FLAGS *flag, char *name_file, int i, int c_files);
void out_for_c_l_(FLAGS *flag, int c_files, int matches, char *name_file);
int flag_f(char **buf, int _ind_);
void flag_o(regex_t reg, char *str, regmatch_t *pmatch, int first_line,
            char *name_file, int num_files);
void v_flag(int *match);

#endif  // S21_GREP_H_"