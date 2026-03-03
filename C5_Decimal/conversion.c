#include <limits.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  if (dst == NULL) return S21_DECIMAL_CONVERT_ERROR;
  s21_init_decimal(dst);

  if (src == 0) return S21_DECIMAL_OK;

  unsigned int abs_src;

  if (src == INT_MIN)
    abs_src = 2147483648U;
  else
    abs_src = src < 0 ? -src : src;

  s21_set_sign(dst, src < 0);
  dst->bits[0] = abs_src;
  return S21_DECIMAL_OK;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  if (!dst) return S21_DECIMAL_CONVERT_ERROR;

  s21_init_decimal(dst);

  if (isnan(src) || isinf(src)) return S21_DECIMAL_CONVERT_ERROR;

  if (src == 0.0f) {
    s21_set_sign(dst, signbit(src));
    return S21_DECIMAL_OK;
  }

  double src_d = fabs((double)src);

  if (src_d < 1e-28) {
    s21_set_sign(dst, signbit(src));
    return S21_DECIMAL_CONVERT_ERROR;
  }
  if (src_d > 7.9228162514264337593543950335e28)
    return S21_DECIMAL_CONVERT_ERROR;

  int exp = 0;

  if (src_d < 1.0) {
    while (src_d < 1.0) {
      src_d *= 10.0;
      exp--;
    }
  } else {
    while (src_d >= 10.0) {
      src_d /= 10.0;
      exp++;
    }
  }

  s21_big_decimal big = {0};

  for (int i = 0; i < 8; i++) {
    int digit = (int)src_d;
    src_d = (src_d - digit) * 10.0;
    s21_big_mul_by_10(&big);
    big.bits[0] += digit;
  }

  int rem;
  big = s21_big_div_by_10(big, &rem);

  if (rem > 5 || (rem == 5 && (big.bits[0] & 1)))
    s21_big_add_mantissa(big, (s21_big_decimal){{1, 0, 0, 0, 0, 0}, 0, 0},
                         &big);

  if (big.bits[5] != 0) {
    big = s21_big_div_by_10(big, NULL);
    exp++;
  }

  int scale = 6 - exp;
  int sign = src < 0;
  big.scale = scale;
  big.sign = sign;

  if (s21_big_to_decimal(big, dst) != S21_DECIMAL_OK)
    return S21_DECIMAL_CONVERT_ERROR;

  s21_set_scale(dst, scale);
  s21_set_sign(dst, sign);

  return S21_DECIMAL_OK;
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  if (!dst) return S21_DECIMAL_CONVERT_ERROR;
  s21_decimal tmp;
  s21_init_decimal(&tmp);
  if (s21_truncate(src, &tmp) != S21_DECIMAL_OK)
    return S21_DECIMAL_CONVERT_ERROR;

  if (tmp.bits[1] != 0 || tmp.bits[2] != 0) return S21_DECIMAL_CONVERT_ERROR;

  int sign = s21_get_sign(tmp);
  unsigned int value = tmp.bits[0];

  if ((!sign && value > INT_MAX) || (sign && value > (unsigned int)INT_MAX + 1))
    return S21_DECIMAL_CONVERT_ERROR;

  *dst = sign ? -(int)value : (int)value;
  return S21_DECIMAL_OK;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  if (!dst) return S21_DECIMAL_CONVERT_ERROR;

  s21_big_decimal big;
  s21_decimal_to_big(src, &big);

  double result = 0.0;

  for (int i = S21_BIG_DECIMAL_BITS_SIZE - 1; i >= 0; i--) {
    result *= pow(2.0, 32);
    result += (unsigned int)big.bits[i];
  }
  for (int i = 0; i < big.scale; i++) result /= 10.0;

  if (big.sign) result = -result;

  *dst = (float)result;
  return S21_DECIMAL_OK;
}
