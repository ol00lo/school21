#include <float.h>
#include <limits.h>
#include <math.h>

#include "test_decimal.h"

// ==================== HELPER FUNCTIONS ====================

static void run_float_test(float src, int expected_ret, int expected_sign) {
  s21_decimal result;
  int ret = s21_from_float_to_decimal(src, &result);

  ck_assert_int_eq(ret, expected_ret);
  if (expected_ret == S21_DECIMAL_OK) {
    ck_assert_int_eq(s21_get_sign(result), expected_sign);
  }
}

static void run_float_conversion_test(float src) {
  s21_decimal result;
  int ret = s21_from_float_to_decimal(src, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);

  float back;
  s21_from_decimal_to_float(result, &back);
  ck_assert_float_eq_tol(back, src, fabsf(src) * 0.0001f + 0.0001f);
}

// ==================== INT TESTS ====================

START_TEST(test_int_common) {
  s21_decimal result;
  int src = 12345;

  ck_assert_int_eq(s21_from_int_to_decimal(src, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(s21_get_sign(result), 0);
  ck_assert_int_eq(s21_get_scale(result), 0);
}
END_TEST

START_TEST(test_int_negative) {
  s21_decimal result;
  int src = -12345;

  ck_assert_int_eq(s21_from_int_to_decimal(src, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(test_int_zero) {
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(0, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_int_max) {
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(INT_MAX, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result.bits[0], INT_MAX);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_int_min) {
  s21_decimal result;

  ck_assert_int_eq(s21_from_int_to_decimal(INT_MIN, &result), S21_DECIMAL_OK);
  ck_assert_uint_eq((unsigned int)result.bits[0], 0x80000000U);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(test_int_null) {
  ck_assert_int_eq(s21_from_int_to_decimal(123, NULL),
                   S21_DECIMAL_CONVERT_ERROR);
}
END_TEST

// ==================== FLOAT TESTS ====================

START_TEST(test_float_simple) {
  run_float_conversion_test(123.456f);
  run_float_conversion_test(-123.456f);
}
END_TEST

START_TEST(test_float_zero) {
  s21_decimal result;

  ck_assert_int_eq(s21_from_float_to_decimal(0.0f, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_zero(result), 1);
  ck_assert_int_eq(s21_get_sign(result), 0);

  ck_assert_int_eq(s21_from_float_to_decimal(-0.0f, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_zero(result), 1);
  ck_assert_int_eq(s21_get_sign(result), 1);
}
END_TEST

START_TEST(test_float_special) {
  run_float_test(NAN, S21_DECIMAL_CONVERT_ERROR, 0);
  run_float_test(INFINITY, S21_DECIMAL_CONVERT_ERROR, 0);
  run_float_test(-INFINITY, S21_DECIMAL_CONVERT_ERROR, 0);
}
END_TEST

START_TEST(test_float_boundaries) {
  run_float_test(1.1e-28f, S21_DECIMAL_OK, 0);
  run_float_test(1e-29f, S21_DECIMAL_CONVERT_ERROR, 0);

  run_float_test(7.9e28f, S21_DECIMAL_OK, 0);
  run_float_test(8e28f, S21_DECIMAL_CONVERT_ERROR, 0);
}
END_TEST

START_TEST(test_float_significant_digits) {
  run_float_conversion_test(1234567.0f);
  run_float_conversion_test(1.234567f);

  s21_decimal result;
  float src = 1.23456789f;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), S21_DECIMAL_OK);

  float back;
  s21_from_decimal_to_float(result, &back);
  ck_assert_float_eq_tol(back, 1.234568f, 0.000001f);
}
END_TEST

START_TEST(test_float_bankers_rounding) {
  s21_decimal result;
  float back;

  float src[] = {1.2345675f, 1.234565f, 1.234575f};
  float expected[] = {1.234568f, 1.234566f, 1.234576f};

  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(s21_from_float_to_decimal(src[i], &result),
                     S21_DECIMAL_OK);
    s21_from_decimal_to_float(result, &back);
    ck_assert_float_eq_tol(back, expected[i], 0.00001f);
  }
}
END_TEST

START_TEST(test_float_negative) {
  float cases[] = {-1.5f, -2.5f, -123.456f, -0.001f};

  for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
    s21_decimal result;
    ck_assert_int_eq(s21_from_float_to_decimal(cases[i], &result),
                     S21_DECIMAL_OK);
    ck_assert_int_eq(s21_get_sign(result), 1);
  }
}
END_TEST

START_TEST(test_float_fractions) {
  run_float_conversion_test(0.000001f);
  run_float_conversion_test(0.123456f);
}
END_TEST

START_TEST(test_float_null) {
  ck_assert_int_eq(s21_from_float_to_decimal(123.456f, NULL),
                   S21_DECIMAL_CONVERT_ERROR);
}
END_TEST

// ==================== DECIMAL TO INT TESTS ====================

START_TEST(test_decimal_to_int_positive) {
  s21_decimal dec;
  int result;

  s21_from_int_to_decimal(12345, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, 12345);
}
END_TEST

START_TEST(test_decimal_to_int_negative) {
  s21_decimal dec;
  int result;

  s21_from_int_to_decimal(-12345, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, -12345);
}
END_TEST

START_TEST(test_decimal_to_int_zero) {
  s21_decimal dec;
  int result;

  s21_from_int_to_decimal(0, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, 0);

  s21_set_sign(&dec, 1);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_to_int_fraction_truncate) {
  s21_decimal dec;
  int result;

  s21_from_int_to_decimal(123.456f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, 123);

  s21_from_int_to_decimal(-123.456f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, -123);

  s21_from_int_to_decimal(0.999f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_to_int_boundary) {
  s21_decimal dec;
  int result;

  s21_from_int_to_decimal(INT_MAX, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, INT_MAX);

  s21_from_int_to_decimal(INT_MIN, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &result), S21_DECIMAL_OK);
  ck_assert_int_eq(result, INT_MIN);
}
END_TEST

START_TEST(test_decimal_to_int_null_pointer) {
  s21_decimal dec;
  s21_from_int_to_decimal(123, &dec);

  ck_assert_int_eq(s21_from_decimal_to_int(dec, NULL),
                   S21_DECIMAL_CONVERT_ERROR);
}
END_TEST

// ==================== DECIMAL TO FLOAT TESTS ====================

START_TEST(test_decimal_to_float_positive) {
  s21_decimal dec;
  float result;

  s21_from_float_to_decimal(123.456f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert_float_eq_tol(result, 123.456f, 0.001f);
}
END_TEST

START_TEST(test_decimal_to_float_negative) {
  s21_decimal dec;
  float result;

  s21_from_float_to_decimal(-123.456f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert_float_eq_tol(result, -123.456f, 0.001f);
}
END_TEST

START_TEST(test_decimal_to_float_zero) {
  s21_decimal dec;
  float result;

  s21_from_int_to_decimal(0, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert_float_eq(result, 0.0f);

  s21_set_sign(&dec, 1);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert(result == -0.0f);
}
END_TEST

START_TEST(test_decimal_to_float_small) {
  s21_decimal dec;
  float result;

  s21_from_float_to_decimal(0.000001f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert_float_eq_tol(result, 0.000001f, 0.0000001f);

  s21_from_float_to_decimal(1e-10f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert_float_eq_tol(result, 1e-10f, 1e-11f);
}
END_TEST

START_TEST(test_decimal_to_float_precision) {
  s21_decimal dec;
  float result;

  s21_from_float_to_decimal(0.1f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert_float_eq_tol(result, 0.1f, 0.0001f);

  s21_from_float_to_decimal(0.2f, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
  ck_assert_float_eq_tol(result, 0.2f, 0.0001f);
}
END_TEST

START_TEST(test_decimal_to_float_round_trip) {
  float test_values[] = {1.5f,   2.5f,       3.5f, 4.5f,      123.456f,
                         0.001f, 1000000.0f, 0.0f, -123.456f, -0.001f};

  for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
    s21_decimal dec;
    float result;

    s21_from_float_to_decimal(test_values[i], &dec);
    ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);

    float tolerance = fabsf(test_values[i]) * 0.0001f + 0.0001f;
    ck_assert_float_eq_tol(result, test_values[i], tolerance);
  }
}
END_TEST

START_TEST(test_decimal_to_float_overflow) {
  s21_decimal dec;
  float result;

  s21_from_float_to_decimal(FLT_MAX, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &result), S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_decimal_to_float_null_pointer) {
  s21_decimal dec;
  s21_from_int_to_decimal(123, &dec);

  ck_assert_int_eq(s21_from_decimal_to_float(dec, NULL),
                   S21_DECIMAL_CONVERT_ERROR);
}
END_TEST

// ==================== TEST SUITES ====================

Suite *int_conversion_suite(void) {
  Suite *s = suite_create("Int Conversion");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_int_common);
  tcase_add_test(tc, test_int_negative);
  tcase_add_test(tc, test_int_zero);
  tcase_add_test(tc, test_int_max);
  tcase_add_test(tc, test_int_min);
  tcase_add_test(tc, test_int_null);

  suite_add_tcase(s, tc);
  return s;
}

Suite *float_conversion_suite(void) {
  Suite *s = suite_create("Float Conversion");
  TCase *tc_core = tcase_create("Core");
  TCase *tc_edge = tcase_create("Edge Cases");

  tcase_add_test(tc_core, test_float_simple);
  tcase_add_test(tc_core, test_float_zero);
  tcase_add_test(tc_core, test_float_significant_digits);
  tcase_add_test(tc_core, test_float_bankers_rounding);
  tcase_add_test(tc_core, test_float_negative);
  tcase_add_test(tc_core, test_float_fractions);
  tcase_add_test(tc_core, test_float_null);

  tcase_add_test(tc_edge, test_float_special);
  tcase_add_test(tc_edge, test_float_boundaries);

  suite_add_tcase(s, tc_core);
  suite_add_tcase(s, tc_edge);
  return s;
}

Suite *decimal_to_int_suite(void) {
  Suite *s = suite_create("Decimal to Int");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_decimal_to_int_positive);
  tcase_add_test(tc, test_decimal_to_int_negative);
  tcase_add_test(tc, test_decimal_to_int_zero);
  tcase_add_test(tc, test_decimal_to_int_fraction_truncate);
  tcase_add_test(tc, test_decimal_to_int_boundary);
  tcase_add_test(tc, test_decimal_to_int_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}

Suite *decimal_to_float_suite(void) {
  Suite *s = suite_create("Decimal to Float");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_decimal_to_float_positive);
  tcase_add_test(tc, test_decimal_to_float_negative);
  tcase_add_test(tc, test_decimal_to_float_zero);
  tcase_add_test(tc, test_decimal_to_float_small);
  tcase_add_test(tc, test_decimal_to_float_precision);
  tcase_add_test(tc, test_decimal_to_float_round_trip);
  tcase_add_test(tc, test_decimal_to_float_overflow);
  tcase_add_test(tc, test_decimal_to_float_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}
