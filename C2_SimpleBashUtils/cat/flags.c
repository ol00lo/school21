#include "flags.h"

#include <getopt.h>
#include <stdio.h>

void flags_initialize(Flags *f) {
  f->number_nonblank = 0;
  f->show_ends = 0;
  f->number = 0;
  f->squeeze_blank = 0;
  f->show_tabs = 0;

  f->not_print_ = 0;
}

int set_flag(char opt, Flags *flags) {
  int res = 0;
  switch (opt) {
    case 'b':
      flags->number_nonblank = 1;
      break;
    case 'e':
      flags->show_ends = 1;
      flags->not_print_ = 1;
      break;
    case 'E':
      flags->show_ends = 1;
      break;
    case 'n':
      flags->number = 1;
      break;
    case 's':
      flags->squeeze_blank = 1;
      break;
    case 't':
      flags->show_tabs = 1;
      flags->not_print_ = 1;
      break;
    case 'T':
      flags->show_tabs = 1;
      break;
    case 'v':
      flags->not_print_ = 1;
      break;
    default:
      fprintf(stderr, "s21_cat: invalid option: '%c'\n", opt);
      res = 1;
  }
  return res;
}

int parse_flags(int argc, char *argv[], Flags *flags) {
  int opt;
  int i = 0;
  int res = 0;

  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, "beEnstTv", long_options, &i)) != -1) {
    if (set_flag(opt, flags) != 0) {
      res = 1;
      break;
    }
  }

  if (flags->number_nonblank && flags->number) flags->number = 0;

  return res;
}
