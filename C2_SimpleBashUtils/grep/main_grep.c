#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "grep.h"

int main(int argc, char **argv) {
  Flags flags;
  int first_file_index = 0;
  int res = 0;

  if (parse_flags(argc, argv, &flags, &first_file_index) != 0) {
    fprintf(stderr, "s21_grep [-ivcln] [-e pattern] [-f file] [files...]\n");
    res = 1;
  } else if (flags.pattern_count == 0) {
    fprintf(stderr, "No pattern provided\n");
    res = 1;
  } else if (first_file_index >= argc) {
    fprintf(stderr, "No input files\n");
    res = 1;
  } else {
    my_grep(first_file_index, argc, argv, &flags);
    flags_free(&flags);
  }

  return res;
}
