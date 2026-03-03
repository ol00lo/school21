#include "test_decimal.h"

START_TEST(test_s21_floor_positive) {
  s21_decimal input = {{12345, 0, 0, 0}};  // 123.45
  s21_set_scale(&input, 2);

  s21_decimal expected = {{123, 0, 0, 0}};  // 123
  s21_set_scale(&expected, 0);

  s21_decimal result = {0};
  int ret = s21_floor(input, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_negative) {
  s21_decimal input = {{12345, 0, 0, 0x80000000}};  // -123.45
  s21_set_scale(&input, 2);

  s21_decimal expected = {{124, 0, 0, 0x80000000}};  // -124
  s21_set_scale(&expected, 0);

  s21_decimal result = {0};
  int ret = s21_floor(input, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_positive_half_up) {
  s21_decimal input = {{1235, 0, 0, 0}};  // 123.5
  s21_set_scale(&input, 1);

  s21_decimal expected = {{124, 0, 0, 0}};  // 124
  s21_set_scale(&expected, 0);

  s21_decimal result = {0};
  int ret = s21_round(input, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_negative_half_down) {
  s21_decimal input = {{1235, 0, 0, 0x80000000}};  // -123.5
  s21_set_scale(&input, 1);

  s21_decimal expected = {{124, 0, 0, 0x80000000}};  // -124
  s21_set_scale(&expected, 0);

  s21_decimal result = {0};
  int ret = s21_round(input, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_simple) {
  s21_decimal input = {{12345, 0, 0, 0}};  // 123.45
  s21_set_scale(&input, 2);

  s21_decimal expected = {{123, 0, 0, 0}};  // 123
  s21_set_scale(&expected, 0);

  s21_decimal result = {0};
  int ret = s21_truncate(input, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_negate_positive_to_negative) {
  s21_decimal input = {{12345, 0, 0, 0}};              // 12345
  s21_decimal expected = {{12345, 0, 0, 0x80000000}};  // -12345
  s21_decimal result = {0};

  int ret = s21_negate(input, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_negate_negative_to_positive) {
  s21_decimal input = {{12345, 0, 0, 0x80000000}};  // -12345
  s21_decimal expected = {{12345, 0, 0, 0}};        // 12345
  s21_decimal result = {0};

  int ret = s21_negate(input, &result);

  ck_assert_int_eq(ret, S21_DECIMAL_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

Suite* create_other_suite() {
  Suite* s = suite_create("s21_decimal_other");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_floor_positive);
  tcase_add_test(tc_core, test_s21_floor_negative);
  tcase_add_test(tc_core, test_s21_round_positive_half_up);
  tcase_add_test(tc_core, test_s21_round_negative_half_down);
  tcase_add_test(tc_core, test_s21_truncate_simple);
  tcase_add_test(tc_core, test_s21_negate_positive_to_negative);
  tcase_add_test(tc_core, test_s21_negate_negative_to_positive);

  suite_add_tcase(s, tc_core);

  return s;
}
