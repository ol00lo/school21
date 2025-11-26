#include "grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compile_patterns(const Flags* flags, regex_t** regexes) {
  int res = 1;

  *regexes = malloc(flags->pattern_count * sizeof(regex_t));

  if (!*regexes) {
    res = 0;
  } else {
    int cflags = REG_NOSUB | REG_NEWLINE;
    if (flags->ignore_case) cflags |= REG_ICASE;

    for (int i = 0; i < flags->pattern_count && res == 1; ++i) {
      // int regcomp(regex_t *preg, const char *pattern, int cflags);
      int ret = regcomp(&(*regexes)[i], flags->patterns[i], cflags);
      if (ret != 0) {
        char buf[256];
        regerror(ret, &(*regexes)[i], buf, sizeof(buf));
        fprintf(stderr, "Regex compilation error: %s\n", buf);
        res = 0;

        for (int j = 0; j < i; ++j) {
          regfree(&(*regexes)[j]);
        }

        free(*regexes);
        *regexes = NULL;
      }
    }
  }

  return res;
}

int match_line(const char* line, const Flags* flags, regex_t* regexes) {
  int res = 0;

  for (int i = 0; i < flags->pattern_count; ++i) {
    // int regexec(const regex_t *compreg,
    // const char *string, size_t nmatch,
    // regmatch_t pmatch[], int eflags);
    if (regexec(&regexes[i], line, 0, NULL, 0) == 0) {
      res = 1;
      break;
    }
  }

  if (flags->invert) res = !res;
  return res;
}

void check_file(const char* filename, const Flags* flags, regex_t* regexes) {
  FILE* fp = fopen(filename, "r");

  if (!fp) {
    if (!flags->count && !flags->list_files) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    }
  } else {
    char* line = NULL;
    size_t n = 0;
    ssize_t read;
    size_t line_number = 1;
    int match_count = 0;
    int file_has_match = 0;

    while ((read = getline(&line, &n, fp)) != -1) {
      int matched = match_line(line, flags, regexes);

      if (matched) {
        file_has_match = 1;
        match_count++;

        if (!flags->count && !flags->list_files) {
          if (flags->number) printf("%zu:", line_number);
          printf("%s", line);
        }
      }

      line_number++;
    }

    if (flags->count) {
      printf("%d\n", match_count);
    }

    if (flags->list_files && file_has_match) {
      printf("%s\n", filename);
    }

    free(line);
    fclose(fp);
  }
}

void my_grep(int first_file_index, int argc, char** argv, Flags* flags) {
  regex_t* regexes = NULL;

  if (flags->pattern_count != 0 && compile_patterns(flags, &regexes)) {
    for (int i = first_file_index; i < argc; ++i) {
      check_file(argv[i], flags, regexes);
    }

    for (int i = 0; i < flags->pattern_count; ++i) {
      regfree(&regexes[i]);
    }
  }

  free(regexes);
}