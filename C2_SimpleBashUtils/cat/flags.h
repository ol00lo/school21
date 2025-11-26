#ifndef FLAGS_H
#define FLAGS_H

typedef struct {
  // -b (GNU: --number-nonblank)
  int number_nonblank;
  // -e implies -v (GNU only: -E the same, but without implying -v)
  int show_ends;
  // -n (GNU: --number)
  int number;
  // -s (GNU: --squeeze-blank)
  int squeeze_blank;
  // -t implies -v (GNU: -T the same, but without implying -v)
  int show_tabs;

  // -v help
  int not_print_;
} Flags;

void flags_initialize(Flags *f);

int set_flag(char opt, Flags *flags);

int parse_flags(int argc, char *argv[], Flags *flags);

#endif