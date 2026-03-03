#include "s21_decimal.h"

#define OK_ARITHMETIC 0
#define LARGE_ARITHMETIC 1
#define SMALL_ARITHMRTIC 2
#define DIV_BY_ZERO_ARITHMRTIC 3

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int code = OK_ARITHMETIC;
  s21_big_decimal v1, v2, temp_res = {0};

  s21_decimal_to_big(value_1, &v1);
  s21_decimal_to_big(value_2, &v2);

  if (s21_is_zero(value_1) || s21_is_zero(value_2)) {
    if (s21_is_zero(value_1)) {
      s21_copy_decimal(value_2, result);
    } else {
      s21_copy_decimal(value_1, result);
    }
  } else {
    s21_big_normalize(&v1, &v2);
    temp_res.scale = v1.scale;
    if (v1.sign == v2.sign) {
      temp_res.sign = v1.sign;
      s21_big_add_mantissa(v1, v2, &temp_res);
    } else {
      if (s21_big_compare_mantissa(v1, v2) >= 0) {
        temp_res.sign = v1.sign;
        s21_big_sub_mantissa(v1, v2, &temp_res);
      } else {
        temp_res.sign = v2.sign;
        s21_big_sub_mantissa(v2, v1, &temp_res);
      }
    }
    code = s21_big_to_decimal(temp_res, result);
  }
  if (s21_is_zero(*result)) {
    s21_set_sign(result, 0);
    s21_set_scale(result, 0);
  }
  return code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_set_sign(&value_2, !s21_get_sign(value_2));
  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int code = OK_ARITHMETIC;
  s21_big_decimal v1, v2, temp_res = {0};

  s21_decimal_to_big(value_1, &v1);
  s21_decimal_to_big(value_2, &v2);

  temp_res.sign = v1.sign ^ v2.sign;

  temp_res.scale = v1.scale + v2.scale;

  s21_big_mul_mantissa(v1, v2, &temp_res);

  code = s21_big_to_decimal(temp_res, result);

  if (s21_is_zero(*result)) {
    s21_set_sign(result, 0);
    s21_set_scale(result, 0);
  }

  return code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int code = OK_ARITHMETIC;
  int done = 0;

  if (s21_is_zero(value_2)) {
    code = DIV_BY_ZERO_ARITHMRTIC;
    done = 1;
  }
  if (!done && s21_is_zero(value_1)) {
    s21_init_decimal(result);
    code = OK_ARITHMETIC;
    done = 1;
  }
  if (!done) {
    s21_big_decimal v1, v2, temp_res = {0}, remainder = {0};

    s21_decimal_to_big(value_1, &v1);
    s21_decimal_to_big(value_2, &v2);

    temp_res.sign = v1.sign ^ v2.sign;

    int res_scale = v1.scale - v2.scale;

    s21_big_div_mantissa(v1, v2, &temp_res, &remainder);

    while (!s21_big_is_zero(remainder) && res_scale < 28) {
      s21_big_mul_by_10(&remainder);
      s21_big_decimal temp_q = {0};
      s21_big_div_mantissa(remainder, v2, &temp_q, &remainder);
      s21_big_mul_by_10(&temp_res);
      s21_big_add_mantissa(temp_res, temp_q, &temp_res);
      res_scale++;
    }
    while (res_scale < 0) {
      s21_big_mul_by_10(&temp_res);
      res_scale++;
    }

    temp_res.scale = res_scale;
    code = s21_big_to_decimal(temp_res, result);

    if (s21_is_zero(*result)) {
      s21_set_sign(result, 0);
      s21_set_scale(result, 0);
    }
  }
  return code;
}