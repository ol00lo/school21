#include "test_decimal.h"

// ============================================================================
// ТЕСТЫ ДЛЯ s21_add
// ============================================================================

START_TEST(test_add_simple) {
  s21_decimal a = {{0x321, 0x321, 0x321, 0x0}};
  s21_decimal b = {{0x123, 0x123, 0x123, 0x0}};
  s21_decimal result;
  s21_decimal check = {{0x444, 0x444, 0x444, 0x0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_different_signs) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal b = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_both_negative) {
  s21_decimal a = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  s21_decimal b = {{0xBBBBBBBC, 0xBBBBBBBB, 0x3BBBBBBB, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_different_scale) {
  s21_decimal a = {{0x28F5C28F, 0xF5C28F5C, 0x028F5C28, 0x1A0000}};
  s21_decimal b = {{0xCCCCCCCC, 0xCCCCCCCC, 0x0CCCCCCC, 0x1B0000}};
  s21_decimal result;
  s21_decimal check = {{0x66666662, 0x66666666, 0x26666666, 0x1B0000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_positive_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ;
  s21_decimal b = {{1, 0, 0, 0x0}};
  s21_decimal result;

  ck_assert_int_eq(s21_add(a, b, &result), 1);
}
END_TEST

START_TEST(test_add_negative_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result;

  ck_assert_int_eq(s21_add(a, b, &result), 2);
}
END_TEST

START_TEST(test_add_rounding_to_even) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x00010000}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_rounding_big_scale) {
  s21_decimal a = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_one_zero) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00110000}};
  s21_decimal b = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00110000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_zeros) {
  s21_decimal a = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal b = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_add_max_mantissa) {
  s21_decimal a = {{0xFFFFFFFF, 0x0000FFFF, 0x0, 0x0}};
  s21_decimal b = {{0x0, 0xFFFF0000, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

// ============================================================================
// ТЕСТЫ ДЛЯ s21_sub
// ============================================================================

START_TEST(test_sub_positive_numbers) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{50, 0, 0, 0}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 50);
}
END_TEST

START_TEST(test_sub_negative_result) {
  s21_decimal a = {{50, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(test_sub_result_zero) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_sub_negative_numbers) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{50, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(test_sub_positive_minus_negative) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{50, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_sub(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 150);
}
END_TEST

// ============================================================================
// ТЕСТЫ ДЛЯ s21_mul
// ============================================================================

START_TEST(test_mul_positive_numbers) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 50);
}
END_TEST

START_TEST(test_mul_negative_numbers) {
  s21_decimal a = {{10, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_mul(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_mul_positive_and_negative) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_mul(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(test_mul_by_zero) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_mul_by_one) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_mul_large_numbers) {
  s21_decimal a = {{100000, 0, 0, 0}};
  s21_decimal b = {{100000, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(a, b, &result);

  ck_assert(code == S21_DECIMAL_OK || code == S21_DECIMAL_OVERFLOW);
}
END_TEST

// ============================================================================
// ТЕСТЫ ДЛЯ s21_div
// ============================================================================

START_TEST(test_div_positive_numbers) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal result;

  int code = s21_div(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 10);
}
END_TEST

START_TEST(test_div_negative_numbers) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{10, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_div(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 10);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_div_positive_and_negative) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0x80000000}};
  s21_decimal result;

  int code = s21_div(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 10);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(test_div_by_zero) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;

  int code = s21_div(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_DIV_BY_ZERO);
}
END_TEST

START_TEST(test_div_zero_by_number) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal result;

  int code = s21_div(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_div_by_one) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;

  int code = s21_div(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
  ck_assert_uint_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_div_with_remainder) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;

  int code = s21_div(a, b, &result);

  ck_assert_int_eq(code, S21_DECIMAL_OK);
}
END_TEST

// ============================================================================
// SUITE CREATION
// ============================================================================

Suite* s21_add_suite(void) {
  Suite* s = suite_create("s21_add");
  TCase* tc = tcase_create("add_tests");

  tcase_add_test(tc, test_add_simple);
  tcase_add_test(tc, test_add_different_signs);
  tcase_add_test(tc, test_add_both_negative);
  tcase_add_test(tc, test_add_different_scale);
  tcase_add_test(tc, test_add_one_zero);
  tcase_add_test(tc, test_add_zeros);
  tcase_add_test(tc, test_add_max_mantissa);
  tcase_add_test(tc, test_add_positive_overflow);
  tcase_add_test(tc, test_add_negative_overflow);
  tcase_add_test(tc, test_add_rounding_to_even);
  tcase_add_test(tc, test_add_rounding_big_scale);

  suite_add_tcase(s, tc);
  return s;
}

Suite* s21_sub_suite(void) {
  Suite* s = suite_create("s21_sub");
  TCase* tc = tcase_create("sub_tests");

  tcase_add_test(tc, test_sub_positive_numbers);
  tcase_add_test(tc, test_sub_negative_result);
  tcase_add_test(tc, test_sub_result_zero);
  tcase_add_test(tc, test_sub_negative_numbers);
  tcase_add_test(tc, test_sub_positive_minus_negative);

  suite_add_tcase(s, tc);
  return s;
}

Suite* s21_mul_suite(void) {
  Suite* s = suite_create("s21_mul");
  TCase* tc = tcase_create("mul_tests");

  tcase_add_test(tc, test_mul_positive_numbers);
  tcase_add_test(tc, test_mul_negative_numbers);
  tcase_add_test(tc, test_mul_positive_and_negative);
  tcase_add_test(tc, test_mul_by_zero);
  tcase_add_test(tc, test_mul_by_one);
  tcase_add_test(tc, test_mul_large_numbers);

  suite_add_tcase(s, tc);
  return s;
}

Suite* s21_div_suite(void) {
  Suite* s = suite_create("s21_div");
  TCase* tc = tcase_create("div_tests");

  tcase_add_test(tc, test_div_positive_numbers);
  tcase_add_test(tc, test_div_negative_numbers);
  tcase_add_test(tc, test_div_positive_and_negative);
  tcase_add_test(tc, test_div_by_zero);
  tcase_add_test(tc, test_div_zero_by_number);
  tcase_add_test(tc, test_div_by_one);
  tcase_add_test(tc, test_div_with_remainder);

  suite_add_tcase(s, tc);
  return s;
}