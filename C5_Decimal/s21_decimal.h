#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_DECIMAL_FALSE 0
#define S21_DECIMAL_TRUE 1
#define S21_DECIMAL_OK 0
#define S21_DECIMAL_ERROR 1
#define S21_DECIMAL_OVERFLOW 1
#define S21_DECIMAL_UNDERFLOW 2
#define S21_DECIMAL_DIV_BY_ZERO 3
#define S21_DECIMAL_CONVERT_ERROR 1

#define S21_DECIMAL_BITS_SIZE 4
#define S21_BIG_DECIMAL_BITS_SIZE 6

typedef struct {
  int bits[S21_DECIMAL_BITS_SIZE];
} s21_decimal;

typedef struct {
  int bits[S21_BIG_DECIMAL_BITS_SIZE];
  int scale;
  int sign;
} s21_big_decimal;

void s21_init_decimal(s21_decimal* decimal);
int s21_get_sign(s21_decimal decimal);
void s21_set_sign(s21_decimal* decimal, int sign);
int s21_get_scale(s21_decimal decimal);
void s21_set_scale(s21_decimal* decimal, int scale);
int s21_is_zero(s21_decimal decimal);
void s21_copy_decimal(s21_decimal src, s21_decimal* dst);
void s21_bank_round(s21_big_decimal* src);

int s21_decimal_to_big(s21_decimal src, s21_big_decimal* dst);
int s21_big_to_decimal(s21_big_decimal src, s21_decimal* dst);
int s21_big_is_zero(s21_big_decimal big_dec);
int s21_big_compare_mantissa(s21_big_decimal d1, s21_big_decimal d2);
int s21_big_mul_by_10(s21_big_decimal* big_dec);
int s21_big_normalize(s21_big_decimal* num1, s21_big_decimal* num2);
void s21_big_add_mantissa(s21_big_decimal a, s21_big_decimal b,
                          s21_big_decimal* result);
void s21_big_sub_mantissa(s21_big_decimal a, s21_big_decimal b,
                          s21_big_decimal* result);
void s21_big_mul_mantissa(s21_big_decimal v1, s21_big_decimal v2,
                          s21_big_decimal* result);
void s21_big_div_mantissa(s21_big_decimal dividend, s21_big_decimal divisor,
                          s21_big_decimal* result, s21_big_decimal* remainder);
s21_big_decimal s21_big_div_by_10(s21_big_decimal a, int* reminder);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);

#endif