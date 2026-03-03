#ifndef SPRINTF_H
#define SPRINTF_H
#include <stdarg.h>

typedef struct {
  int left_align;
  int force_sign;
  int space_sign;
  int alt_form;
  int zero_pad;
  int width;
  int precision;
  int precision_specified;
} FormatSpec;

int parse_flags(char c_ch, const FormatSpec *spec, char *str, int j,
                va_list *args);
int parse_format(const char *format, int i, FormatSpec *spec, va_list *args);
#endif
