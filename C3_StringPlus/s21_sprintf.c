#include "s21_sprintf.h"

#include <stdio.h>

void formatspec_init(FormatSpec* spec) {
  spec->left_align = 0;
  spec->force_sign = 0;
  spec->space_sign = 0;
  spec->alt_form = 0;
  spec->zero_pad = 0;
  spec->width = 0;
  spec->precision = 0;
  spec->precision_specified = 0;
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);

  int i = 0;
  int j = 0;
  while (format[i] != '\0') {
    if (format[i] == '%') {
      i++;
      FormatSpec spec;
      i = parse_format(format, i, &spec, &args);
      j = parse_flags(format[i], &spec, str, j, &args);
      i++;
    } else {
      str[j++] = format[i++];
    }
  }
  str[j] = '\0';
  va_end(args);
  return j;
}

void reverse(char* str, int len) {
  int i = 0;
  int j = len - 1;
  while (i < j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    i++;
    j--;
  }
}

int write_padding(char* str, int j, int count, char ch) {
  for (int i = 0; i < count; i++) str[j++] = ch;
  return j;
}

int int_to_str(int num, char* str) {
  int i = 0;
  int is_negative = num < 0;
  unsigned int n = is_negative ? -num : num;

  if (n == 0) str[i++] = '0';
  while (n > 0) {
    str[i++] = '0' + (n % 10);
    n /= 10;
  }
  if (is_negative) str[i++] = '-';
  str[i] = '\0';
  reverse(str, i);
  return i;
}

int uint_to_str(unsigned int num, char* str) {
  int i = 0;
  if (num == 0) str[i++] = '0';
  while (num > 0) {
    str[i++] = '0' + (num % 10);
    num /= 10;
  }
  str[i] = '\0';
  reverse(str, i);
  return i;
}

int uint_to_str_base(unsigned int num, char* str, int base, int uppercase) {
  const char* digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0;
  if (base < 2 || base > 16) {
    str[0] = '\0';
    return 0;
  }

  if (num == 0) str[i++] = '0';
  while (num > 0) {
    str[i++] = digits[num % base];
    num /= base;
  }
  str[i] = '\0';
  reverse(str, i);
  return i;
}

int float_to_str(double num, char* str, int precision, int alt_form) {
  int i = 0;

  if (num < 0) {
    str[i++] = '-';
    num = -num;
  }

  double rounding = 0.5;
  for (int p = 0; p < precision; p++) rounding /= 10.0;
  num += rounding;

  int int_part = (int)num;
  double frac_part = num - int_part;

  char temp[64];
  int int_len = int_to_str(int_part, temp);
  for (int k = 0; k < int_len; k++) str[i++] = temp[k];

  if (precision > 0 || alt_form) {
    str[i++] = '.';
    for (int p = 0; p < precision; p++) {
      frac_part *= 10.0;
      int digit = (int)frac_part;
      str[i++] = digit + '0';
      frac_part -= digit;
    }
  }
  str[i] = '\0';
  return i;
}

int float_to_sci(double num, char* str, int precision, int uppercase,
                 int alt_form) {
  int i = 0;
  if (num < 0) {
    str[i++] = '-';
    num = -num;
  }
  int exponent = 0;
  if (num != 0.0) {
    while (num >= 10.0) {
      num /= 10.0;
      exponent++;
    }
    while (num > 0 && num < 1.0) {
      num *= 10.0;
      exponent--;
    }
  }

  int int_part = (int)num;
  double frac_part = num - int_part;
  char temp[64];
  int int_len = int_to_str(int_part, temp);
  for (int k = 0; k < int_len; k++) str[i++] = temp[k];

  if (precision > 0 || alt_form) {
    str[i++] = '.';
    for (int p = 0; p < precision; p++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      str[i++] = digit + '0';
      frac_part -= digit;
    }
  }

  str[i++] = uppercase ? 'E' : 'e';
  str[i++] = (exponent >= 0) ? '+' : '-';
  if (exponent < 0) exponent = -exponent;
  str[i++] = '0' + (exponent / 10);
  str[i++] = '0' + (exponent % 10);
  str[i] = '\0';
  return i;
}

int get_num(int* n, const char* format, int i, va_list* args) {
  if (format[i] >= '0' && format[i] <= '9') {
    *n = 0;
    while (format[i] >= '0' && format[i] <= '9') {
      *n = *n * 10 + (format[i] - '0');
      i++;
    }
  } else if (format[i] == '*') {
    *n = va_arg(*args, int);
    i++;
  }
  return i;
}

int write_char(const FormatSpec* spec, char* str, int j, va_list* args) {
  char c = (char)va_arg(*args, int);
  int padding = spec->width - 1;
  if (padding < 0) padding = 0;
  if (!spec->left_align) j = write_padding(str, j, padding, ' ');
  str[j++] = c;
  if (spec->left_align) j = write_padding(str, j, padding, ' ');
  return j;
}

int write_number(const FormatSpec* spec, char* str, int j, const char* num_str,
                 int is_negative) {
  int len = 0;
  while (num_str[len] != '\0') len++;

  int sign_len = 0;
  char sign_char = 0;
  if (is_negative) {
    sign_char = '-';
    sign_len = 1;
  } else if (spec->force_sign) {
    sign_char = '+';
    sign_len = 1;
  } else if (spec->space_sign) {
    sign_char = ' ';
    sign_len = 1;
  }

  int padding = spec->width - len - sign_len;
  if (padding < 0) padding = 0;

  if (!spec->left_align) {
    char pad_char = spec->zero_pad ? '0' : ' ';
    if (spec->zero_pad && sign_char) {
      str[j++] = sign_char;
      sign_char = 0;
    }
    j = write_padding(str, j, padding, pad_char);
  }

  if (sign_char) str[j++] = sign_char;
  for (int k = 0; k < len; k++) str[j++] = num_str[k];
  if (spec->left_align) j = write_padding(str, j, padding, ' ');

  return j;
}

int write_int(const FormatSpec* spec, char* str, int j, va_list* args) {
  int num = va_arg(*args, int);
  char buffer[32];
  int_to_str(num, buffer);
  return write_number(spec, str, j, buffer, num < 0);
}

int write_uint(const FormatSpec* spec, char* str, int j, va_list* args) {
  unsigned int num = va_arg(*args, unsigned int);
  char buffer[32];
  uint_to_str(num, buffer);
  return write_number(spec, str, j, buffer, 0);
}

int write_string(const FormatSpec* spec, char* str, int j, va_list* args) {
  char* s = va_arg(*args, char*);
  int len = 0;
  while (s[len] != '\0') len++;

  if (spec->precision_specified && len > spec->precision) {
    len = spec->precision;
  }

  int padding = spec->width - len;
  if (padding < 0) padding = 0;

  if (!spec->left_align) j = write_padding(str, j, padding, ' ');

  for (int k = 0; k < len; k++) str[j++] = s[k];

  if (spec->left_align) j = write_padding(str, j, padding, ' ');

  return j;
}

int write_float(const FormatSpec* spec, char* str, int j, va_list* args) {
  double num = va_arg(*args, double);
  int precision = spec->precision_specified ? spec->precision : 6;
  char buffer[128];
  float_to_str(num, buffer, precision, spec->alt_form);
  return write_number(spec, str, j, buffer, num < 0);
}

int write_hex(const FormatSpec* spec, char* str, int j, va_list* args,
              int uppercase) {
  unsigned int num = va_arg(*args, unsigned int);
  char buffer[32];
  int len = uint_to_str_base(num, buffer, 16, uppercase);
  if (spec->alt_form && num != 0) {
    for (int k = len + 2; k >= 2; k--) buffer[k] = buffer[k - 2];
    buffer[0] = '0';
    buffer[1] = uppercase ? 'X' : 'x';
    len += 2;
    buffer[len] = '\0';
  }
  return write_number(spec, str, j, buffer, 0);
}

int write_octal(const FormatSpec* spec, char* str, int j, va_list* args) {
  unsigned int num = va_arg(*args, unsigned int);
  char buffer[32];
  int len = uint_to_str_base(num, buffer, 8, 0);
  if (spec->alt_form && num != 0) {
    for (int k = len; k > 0; k--) buffer[k] = buffer[k - 1];
    buffer[0] = '0';
    len++;
    buffer[len] = '\0';
  }
  return write_number(spec, str, j, buffer, 0);
}

int write_float_e(const FormatSpec* spec, char* str, int j, va_list* args,
                  int uppercase) {
  double num = va_arg(*args, double);
  int precision = spec->precision_specified ? spec->precision : 6;
  char buffer[128];
  float_to_sci(num, buffer, precision, uppercase, spec->alt_form);
  return write_number(spec, str, j, buffer, num < 0);
}

int write_float_g(const FormatSpec* spec, char* str, int j, va_list* args,
                  int uppercase) {
  double num = va_arg(*args, double);
  int precision = spec->precision_specified ? spec->precision : 6;
  double tmp = num;
  int exp = 0;
  if (tmp != 0.0) {
    while (tmp >= 10.0) {
      tmp /= 10;
      exp++;
    }
    while (tmp < 1.0) {
      tmp *= 10;
      exp--;
    }
  }
  if (exp < -4 || exp >= precision) {
    char buffer[128];
    float_to_sci(num, buffer, precision - 1, uppercase, spec->alt_form);
    return write_number(spec, str, j, buffer, num < 0);
  } else {
    return write_float(spec, str, j, args);
  }
}

int write_pointer(const FormatSpec* spec, char* str, int j, va_list* args) {
  void* ptr = va_arg(*args, void*);
  unsigned long addr = (unsigned long)ptr;
  char buffer[32];
  int len = 0;

  buffer[len++] = '0';
  buffer[len++] = 'x';

  if (addr == 0) {
    buffer[len++] = '0';
  } else {
    char tmp[32];
    int tlen = 0;
    while (addr) {
      int r = addr % 16;
      tmp[tlen++] = (r < 10) ? '0' + r : 'a' + r - 10;
      addr /= 16;
    }
    for (int k = tlen - 1; k >= 0; k--) buffer[len++] = tmp[k];
  }
  buffer[len] = '\0';

  int padding = spec->width - len;
  if (padding < 0) padding = 0;
  if (!spec->left_align)
    j = write_padding(str, j, padding, spec->zero_pad ? '0' : ' ');

  for (int k = 0; k < len; k++) str[j++] = buffer[k];
  if (spec->left_align) j = write_padding(str, j, padding, ' ');
  return j;
}

int parse_format(const char* format, int i, FormatSpec* spec, va_list* args) {
  formatspec_init(spec);

  int ready = 0;
  while (!ready) {
    switch (format[i]) {
      case '-':
        spec->left_align = 1;
        i++;
        break;
      case '+':
        spec->force_sign = 1;
        i++;
        break;
      case ' ':
        spec->space_sign = 1;
        i++;
        break;
      case '#':
        spec->alt_form = 1;
        i++;
        break;
      case '0':
        spec->zero_pad = 1;
        i++;
        break;
      default:
        ready = 1;
        break;
    }
  }

  if (spec->left_align) spec->zero_pad = 0;

  i = get_num(&spec->width, format, i, args);

  if (format[i] == '.') {
    i++;
    spec->precision_specified = 1;
    i = get_num(&spec->precision, format, i, args);
  }
  return i;
}

int parse_flags(char c_ch, const FormatSpec* spec, char* str, int j,
                va_list* args) {
  switch (c_ch) {
    case 'c':
      j = write_char(spec, str, j, args);
      break;
    case 'd':
    case 'i':
      j = write_int(spec, str, j, args);
      break;
    case 'e':
      j = write_float_e(spec, str, j, args, 0);
      break;
    case 'E':
      j = write_float_e(spec, str, j, args, 1);
      break;
    case 'f':
      j = write_float(spec, str, j, args);
      break;
    case 'g':
      j = write_float_g(spec, str, j, args, 0);
      break;
    case 'G':
      j = write_float_g(spec, str, j, args, 1);
      break;
    case 'o':
      j = write_octal(spec, str, j, args);
      break;
    case 's':
      j = write_string(spec, str, j, args);
      break;
    case 'u':
      j = write_uint(spec, str, j, args);
      break;
    case 'x':
      j = write_hex(spec, str, j, args, 0);
      break;
    case 'X':
      j = write_hex(spec, str, j, args, 1);
      break;
    case 'p':
      j = write_pointer(spec, str, j, args);
      break;
    case 'n': {
      int* ptr = va_arg(*args, int*);
      *ptr = j;
      break;
    }
    case '%':
      str[j++] = '%';
      break;
    default:
      str[j++] = '%';
      str[j++] = c_ch;
      break;
  }
  return j;
}