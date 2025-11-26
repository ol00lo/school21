#ifndef FLAGS_H
#define FLAGS_H

typedef struct {
  // -i	Ignore uppercase vs. lowercase.
  int ignore_case;
  // -v	Invert match.
  int invert;
  // -c	Output count of matching lines only.
  int count;
  // -l	Output matching files only.
  int list_files;
  // -n	Precede each matching line with a line number.
  int number;

  int pattern_count;
  char **patterns;
} Flags;

void flags_free(Flags *f);
int parse_flags(int argc, char **argv, Flags *flags, int *first_file_index);

#endif
