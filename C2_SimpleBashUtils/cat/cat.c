#include "cat.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

// PARSE ARGUMENTS

void parse_files(int argc, char *argv[], char ***files, int *file_count) {
  *file_count = argc - optind;
  if (*file_count > 0)
    *files = &argv[optind];
  else
    *files = NULL;
}

int parse_arguments(int argc, char *argv[], Flags *flags, char ***files,
                    int *file_count) {
  int res = 0;
  flags_initialize(flags);

  if (parse_flags(argc, argv, flags) != 0) res = 1;

  parse_files(argc, argv, files, file_count);
  return res;
}

// CAT

int is_line_empty(const char *line) {
  int res = 1;
  if (line != NULL) {
    for (int i = 0; line[i] != '\0'; i++) {
      if (line[i] != '\n' && line[i] != '\r' && line[i] != ' ' &&
          line[i] != '\t') {
        res = 0;
        break;
      }
    }
  }
  return res;
}

void change_nonprinting(unsigned char c) {
  if (c < 32 && c != '\t' && c != '\n') {
    printf("^%c", c + 64);
  } else if (c == 127) {
    printf("^?");
  } else {
    printf("%c", c);
  }
}

void output_formatted_line(const char *line, const Flags *flags) {
  for (int i = 0; line[i] != '\0'; i++) {
    unsigned char c = line[i];

    if (flags->show_tabs && c == '\t') {
      printf("^I");
      continue;
    }

    if (flags->show_ends && c == '\n') {
      printf("$\n");
      continue;
    }

    if (flags->not_print_)
      change_nonprinting(c);
    else
      printf("%c", c);
  }
}

void output_line(char *line, const Flags *flags, int *line_num) {
  if (line == NULL) return;

  if (flags->number_nonblank && !is_line_empty(line))
    printf("%6d\t", (*line_num)++);

  if (flags->number) printf("%6d\t", (*line_num)++);

  if (flags->not_print_ || flags->show_tabs || flags->show_ends) {
    output_formatted_line(line, flags);
  } else {
    printf("%s", line);
  }
}

void output_file(FILE *file, const Flags *flags) {
  char buffer[4096];
  int line_number = 1;
  int is_previous_line_empty = 0;

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    char *line = buffer;

    if (flags->squeeze_blank) {
      int is_empty = is_line_empty(line);

      if (is_empty && is_previous_line_empty) {
        continue;
      }
      is_previous_line_empty = is_empty;
    }

    output_line(line, flags, &line_number);
  }
}

void my_cat(const char *filename, const Flags *flags) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "s21_cat: %s: No such file or directory\n", filename);
    return;
  }

  output_file(file, flags);
  fclose(file);
}