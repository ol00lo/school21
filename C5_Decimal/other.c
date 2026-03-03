#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal* result) {
  s21_decimal truncated = {0};
  s21_decimal one = {0};
  one.bits[0] = 1;
  int error = S21_DECIMAL_OK;
  if (s21_truncate(value, &truncated)) {
    error = S21_DECIMAL_ERROR;
  } else if (s21_get_sign(value) == 0) {
    s21_copy_decimal(truncated, result);
  } else {
    if (!s21_is_equal(value, truncated)) {
      if (s21_sub(truncated, one, result)) {
        error = S21_DECIMAL_ERROR;
      }
    } else {
      s21_copy_decimal(truncated, result);
    }
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);
  s21_set_sign(&half, s21_get_sign(value));
  s21_decimal temp = {0};
  int error = S21_DECIMAL_OK;
  if (s21_add(value, half, &temp)) {
    error = S21_DECIMAL_ERROR;
  }
  if (!error) {
    s21_truncate(temp, result);
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  s21_big_decimal big_temp = {0};
  s21_decimal_to_big(value, &big_temp);
  int remainder = 0;
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);

  for (int i = 0; i < scale; i++) {
    big_temp = s21_big_div_by_10(big_temp, &remainder);
  }

  big_temp.scale = 0;
  big_temp.sign = sign;
  s21_big_to_decimal(big_temp, result);

  return S21_DECIMAL_OK;
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  int value_sign = s21_get_sign(value);
  s21_copy_decimal(value, result);
  s21_set_sign(result, !value_sign);
  return S21_DECIMAL_OK;
}
