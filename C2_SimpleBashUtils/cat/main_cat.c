#include <stdio.h>
#include <string.h>

#include "cat.h"

int main(int argc, char *argv[]) {
  Flags flags;
  char **files = NULL;
  int file_count = 0;

  if (parse_arguments(argc, argv, &flags, &files, &file_count) != 0) return 1;

  if (file_count != 0)
    for (int i = 0; i < file_count; i++) my_cat(files[i], &flags);
  else
    fprintf(stderr, "Not impl");

  return 0;
}