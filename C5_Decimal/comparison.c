#include "s21_decimal.h"

#define FALSE_COMPARISON 0
#define TRUE_COMPARISON 1

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_is_less(s21_decimal a, s21_decimal b) {
  int result = FALSE_COMPARISON;
  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);

  s21_big_decimal A;
  s21_big_decimal B;
  s21_decimal_to_big(a, &A);
  s21_decimal_to_big(b, &B);

  s21_big_normalize(&A, &B);
  if (!s21_big_is_zero(A) || !s21_big_is_zero(B)) {
    if (sign_a != sign_b) {
      result = sign_a;
    } else {
      result = (sign_a == 0) ? (s21_big_compare_mantissa(A, B) == -1)
                             : (s21_big_compare_mantissa(A, B) == 1);
    }
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_less(a, b) || s21_is_equal(a, b);
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  return !s21_is_less(a, b) && !s21_is_equal(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_less(a, b);
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);

  s21_big_decimal A;
  s21_big_decimal B;
  s21_decimal_to_big(a, &A);
  s21_decimal_to_big(b, &B);

  s21_big_normalize(&A, &B);
  return (s21_big_is_zero(A) && s21_big_is_zero(B)) ||
         (sign_a == sign_b && s21_big_compare_mantissa(A, B) == 0);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}
