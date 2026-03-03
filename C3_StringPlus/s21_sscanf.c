#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "s21_string.h"

struct FormatSpecifier {
  const char* start_str;
  unsigned long width;
  int skip;
  char length_modifier;
};

void increase_str_and_count(const char** str, unsigned long* count_char);
int check_chr_integer_base(const char** str, int base);
int string_to_integer_to_base(const char** str, int base, unsigned long* result,
                              int need_sign, unsigned long limit);
int get_arg_by_length_int(const char s, va_list args,
                          struct FormatSpecifier data, void** ptr);
void set_value_by_length(const char s, unsigned long value,
                         long double real_value, struct FormatSpecifier data,
                         void* ptr);
int proccessing_specifier_part1(char s, va_list args, const char** str,
                                struct FormatSpecifier data);
int proccessing_specifier_part2(char s, va_list args, const char** str,
                                struct FormatSpecifier data);
int proccessing_specifier_part3(char s, va_list args, const char** str,
                                struct FormatSpecifier data);

int s21_sscanf(const char* str, const char* format, ...) {
  const char lenght_list[] = {'h', 'l', 'L'},
             specifier_list1[] = {'d', 'i', 'x', 'X', 'u', 'o'},
             specifier_list2[] = {'p', 's', 'c', '%'},
             specifier_list3[] = {'e', 'E', 'f', 'g', 'G', 'n'};

  if (*str == '\0') return -1;
  va_list args;
  va_start(args, format);
  int count = 0, stop = 0;
  struct FormatSpecifier data = {(char*)str, INT32_MAX, 0, -1};
  while (!stop && *format != '\0') {
    data.skip = 0;
    data.width = INT32_MAX;
    data.length_modifier = -1;
    if (*format == ' ')
      while (isspace(*str)) str++;
    else if (*format == '%') {
      format++;
      if (*format == '*') {
        data.skip = 1;
        format++;
      }
      if (check_chr_integer_base(&format, 10))
        string_to_integer_to_base(&format, 10, &data.width, 0, INT32_MAX);
      if (s21_strchr(lenght_list, *format)) data.length_modifier = *format++;
      if (s21_strchr(specifier_list1, *format))
        stop = proccessing_specifier_part1(*format, args, &str, data);
      else if (s21_strchr(specifier_list2, *format))
        stop = proccessing_specifier_part2(*format, args, &str, data);
      else if (s21_strchr(specifier_list3, *format))
        stop = proccessing_specifier_part3(*format, args, &str, data);
      else
        stop = 1;
      if (!stop && !data.skip && *format != 'n' && *format != '%') count++;
    } else {
      if (*format != *str) {
        stop = 1;
      } else {
        str++;
      }
    }
    format++;
  }
  va_end(args);
  return count;
}

int string_to_integer_to_base(const char** str, int base, unsigned long* result,
                              int need_sign, unsigned long limit) {
  int fail = 1, sign = 1;
  unsigned long count = 0;

  *result = 0;
  if (need_sign && (**str == '+' || **str == '-')) {
    sign = (**str == '-') ? -1 : 1;
    (*str)++;
  }
  if (base == 8 || base == 16) {
    if (**str == '0') {
      (*str)++;
      if (base == 16) {
        if (**str == 'x' || **str == 'X') (*str)++;
      }
    }
  }
  while (check_chr_integer_base(str, base) && count < limit) {
    fail = 0;
    char help_char = '0';
    if (**str >= 'A') help_char = (**str >= 'a') ? 'a' - 10 : 'A' - 10;
    *result = *result * base + (**str - help_char);
    (*str)++;
    count++;
  }
  *result *= sign;
  return fail;
}

int check_chr_integer_base(const char** str, int base) {
  int success = 0;

  switch (base) {
    case 8:
      success = (**str >= '0' && **str <= '7');
      break;
    case 10:
      success = (**str >= '0' && **str <= '9');
      break;
    case 16:
      success =
          ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f') ||
           (**str >= 'A' && **str <= 'F'));
      break;
  }
  return success;
}

int get_arg_by_length_int(const char s, va_list args,
                          struct FormatSpecifier data, void** ptr) {
  int fail = 0;
  if (s == 'd' || s == 'i') {
    if (data.length_modifier == -1)
      *ptr = va_arg(args, int*);
    else if (data.length_modifier == 'h')
      *ptr = va_arg(args, short*);
    else if (data.length_modifier == 'l')
      *ptr = va_arg(args, long*);
    else
      fail = 1;
  } else if (s == 'x' || s == 'X' || s == 'u' || s == 'o') {
    if (data.length_modifier == -1)
      *ptr = va_arg(args, unsigned int*);
    else if (data.length_modifier == 'h')
      *ptr = va_arg(args, unsigned short*);
    else if (data.length_modifier == 'l')
      *ptr = va_arg(args, unsigned long*);
    else
      fail = 1;
  } else if (s == 'e' || s == 'E' || s == 'f' || s == 'g' || s == 'G') {
    if (data.length_modifier == -1)
      *ptr = va_arg(args, float*);
    else if (data.length_modifier == 'L')
      *ptr = va_arg(args, long double*);
    else
      fail = 1;
  }
  return fail;
}

void set_value_by_length(const char s, unsigned long value,
                         long double real_value, struct FormatSpecifier data,
                         void* ptr) {
  if (s == 'd' || s == 'i') {
    if (data.length_modifier == -1)
      *(int*)ptr = value;
    else if (data.length_modifier == 'h')
      *(short*)ptr = value;
    else if (data.length_modifier == 'l')
      *(long*)ptr = value;
  } else if (s == 'x' || s == 'X' || s == 'u' || s == 'o') {
    if (data.length_modifier == -1)
      *(unsigned int*)ptr = value;
    else if (data.length_modifier == 'h')
      *(unsigned short*)ptr = value;
    else if (data.length_modifier == 'l')
      *(unsigned long*)ptr = value;
  } else if (s == 'e' || s == 'E' || s == 'f' || s == 'g' || s == 'G') {
    if (data.length_modifier == -1)
      *(float*)ptr = real_value;
    else if (data.length_modifier == 'L')
      *(long double*)ptr = real_value;
  }
}

int proccessing_specifier_part1(const char s, va_list args, const char** str,
                                struct FormatSpecifier data) {
  int fail = 0;
  void* ptr;
  unsigned long value = 0;
  if (!data.skip) fail = get_arg_by_length_int(s, args, data, &ptr);

  while (isspace(**str)) (*str)++;
  if (!fail && s == 'd') {
    fail = string_to_integer_to_base(str, 10, &value, 1, data.width);
    if (!fail && !data.skip) set_value_by_length(s, value, 0, data, ptr);
  }
  if (!fail && s == 'i') {
    int base;
    if (**str == '0') {
      (*str)++;
      if (**str == 'x' || **str == 'X') {
        base = 16;
        (*str)--;
      } else {
        base = 8;
      }
    } else {
      base = 10;
    }
    fail = string_to_integer_to_base(str, base, &value, 1, data.width);
    if (!fail && !data.skip) set_value_by_length(s, value, 0, data, ptr);
  }
  if (!fail && (s == 'x' || s == 'X' || s == 'u' || s == 'o')) {
    int base = ((s == 'x' || s == 'X')) ? 16 : (s == 'u') ? 10 : 8;
    fail = string_to_integer_to_base(str, base, &value, 0, data.width);
    if (!fail && !data.skip) set_value_by_length(s, value, 0, data, ptr);
  }
  return fail;
}

int proccessing_specifier_part2(char s, va_list args, const char** str,
                                struct FormatSpecifier data) {
  int fail = 0;

  while (isspace(**str)) (*str)++;
  if (s == 's') {
    char* ptr = va_arg(args, char*);
    while (isspace(**str)) (*str)++;
    if (**str == '\0') fail = 1;
    char* start_ptr = ptr;
    if (!fail && !data.skip) {
      for (unsigned long i = 0;
           i < data.width && **str != '\0' && !isspace(**str); i++) {
        *ptr = **str;
        ptr++;
        (*str)++;
      }
      *ptr = '\0';
      if (ptr == start_ptr) fail = 1;
    }
  }
  if (s == 'p') {
    void** ptr;
    if (!data.skip) ptr = va_arg(args, void**);
    unsigned long value = 0;
    fail = string_to_integer_to_base(str, 16, &value, 0, data.width);
    if (!fail && !data.skip) *ptr = (void*)value;
  }
  if (s == 'c') {
    char* ptr = va_arg(args, char*);
    if (!fail && !data.skip) {
      *ptr = *(*str)++;
      if (data.width != INT32_MAX) {
        while (data.width-- > 0) *(++ptr) = *(*str)++;
        *ptr = '\0';
      }
    }
  }
  if (s == '%') {
    while (isspace(**str)) (*str)++;
    if (**str != '%')
      fail = 1;
    else
      (*str)++;
  }
  return fail;
}

int proccessing_specifier_part3(char s, va_list args, const char** str,
                                struct FormatSpecifier data) {
  int fail = 0;

  if (s == 'e' || s == 'E' || s == 'f' || s == 'g' || s == 'G') {
    void* ptr;
    int count_zero_decimal = 0;
    while (isspace(**str)) (*str)++;
    if (!data.skip) fail = get_arg_by_length_int(s, args, data, &ptr);
    unsigned long whole = 0, exponent = 0, decimal = 0;
    fail = fail || string_to_integer_to_base(str, 10, &whole, 1, data.width);
    if (!fail && **str == '.') {
      (*str)++;
      while (*(*str + count_zero_decimal) == '0') count_zero_decimal++;
      fail = string_to_integer_to_base(str, 10, &decimal, 0, data.width);
    }
    if (!fail && (**str == 'e' || **str == 'E')) {
      (*str)++;
      fail = string_to_integer_to_base(str, 10, &exponent, 1, data.width);
    }
    if (!fail && !data.skip) {
      long double value = (long double)whole;
      if (decimal) {
        long double new_decimal = (long double)decimal;
        while (new_decimal >= 1 || count_zero_decimal-- > 0) new_decimal /= 10;
        value += new_decimal;
      }
      if (exponent != 0) value = value * pow(10, (int)exponent);
      set_value_by_length(s, 0, value, data, ptr);
    }
  }
  if (s == 'n') {
    int value = 0;
    while (data.start_str + value != *str) value++;
    if (!data.skip) {
      int* ptr = va_arg(args, int*);
      *ptr = value;
    }
  }
  return fail;
}