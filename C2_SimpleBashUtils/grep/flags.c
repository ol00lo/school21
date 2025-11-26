#include "flags.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flags_initialize(Flags *f) {
  f->ignore_case = 0;
  f->invert = 0;
  f->count = 0;
  f->list_files = 0;
  f->number = 0;

  f->patterns = NULL;
  f->pattern_count = 0;
}

void add_pattern(Flags *f, const char *pattern) {
  f->patterns = realloc(f->patterns, (f->pattern_count + 1) * sizeof(char *));
  f->patterns[f->pattern_count] = strdup(pattern);
  f->pattern_count++;
}

void read_patterns_from_file(Flags *f, const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) return;

  char *line = NULL;
  size_t n = 0;
  while (getline(&line, &n, fp) != -1) {
    line[strcspn(line, "\n")] = 0;
    add_pattern(f, line);
  }
  free(line);
  fclose(fp);
}

void apply_flag(Flags *flags, int opt) {
  switch (opt) {
    case 'i':
      flags->ignore_case = 1;
      break;
    case 'v':
      flags->invert = 1;
      break;
    case 'c':
      flags->count = 1;
      break;
    case 'l':
      flags->list_files = 1;
      break;
    case 'n':
      flags->number = 1;
      break;
  }
}

void apply_pattern_arg(Flags *flags, int opt, const char *arg,
                       int *pattern_set) {
  switch (opt) {
    case 'e':
      add_pattern(flags, arg);
      *pattern_set = 1;
      break;

    case 'f':
      read_patterns_from_file(flags, arg);
      *pattern_set = 1;
      break;
  }
}

int parse_flags(int argc, char **argv, Flags *flags, int *first_file_index) {
  flags_initialize(flags);

  int res = 0;
  int opt;
  int pattern_set = 0;

  while ((opt = getopt(argc, argv, "ivclne:f:")) != -1 && res == 0) {
    if (opt == 'e' || opt == 'f') {
      apply_pattern_arg(flags, opt, optarg, &pattern_set);
      continue;
    }

    if (opt == '?') {
      res = 1;
    } else {
      apply_flag(flags, opt);
    }
  }

  if (res == 0) {
    if (!pattern_set && optind < argc) {
      add_pattern(flags, argv[optind]);
      optind++;
    }
    *first_file_index = optind;
  }
  return res;
}

void flags_free(Flags *f) {
  for (int i = 0; i < f->pattern_count; ++i) {
    free(f->patterns[i]);
  }
  free(f->patterns);
}