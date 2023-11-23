#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;
opt options = {0};
void read_file(char *name_file, char ch, char *command);
int check_flag(int ac, char **av, opt *opts);
int output(char _ch, opt *opts, int i, int flg_n, int flag_b, char _1_before,
           char _2_before);

#endif  // S21_CAT_H_"
