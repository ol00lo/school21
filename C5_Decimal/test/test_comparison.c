#include "test_decimal.h"

START_TEST(test_is_less_less) {
  s21_decimal a = {{0x0, 0x0, 0x80000000, 0x0}};
  s21_decimal b = {{0x0, 0x0, 0xC0000000, 0x0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_greater) {
  s21_decimal a = {{0x1, 0x0, 0xC0000000, 0x0}};
  s21_decimal b = {{0x0, 0x0, 0xC0000000, 0x0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_equal) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_less_greater_different_signs) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_less_different_scale) {
  s21_decimal a = {{0x0FFFFFFF, 0x3E250261, 0x204FCE5E, 0x001C0000}};
  s21_decimal b = {{0xA, 0x0, 0x0, 0x00010000}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST  // 0x204FCE5E 3E250261 0FFFFFFF

START_TEST(test_is_less_equal_different_scale) {
  s21_decimal a = {{0x000186A0, 0x0, 0x0, 0x00050000}};
  s21_decimal b = {{0xA, 0x0, 0x0, 0x00010000}};

  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_less_greater_different_scale_both_negative) {
  s21_decimal a = {{0x0FFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  s21_decimal b = {{0xA, 0x0, 0x0, 0x80010000}};

  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_less_both_negative) {
  s21_decimal a = {{0x0, 0x0, 0xA, 0x80000000}};
  s21_decimal b = {{0xA, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_less_one_zero) {
  s21_decimal a = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal b = {{0x0, 0x0, 0x2134, 0x00140000}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_equal_zeros_different_signs) {
  s21_decimal a = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal b = {{0x0, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_less_less_boundary_bits) {
  s21_decimal a = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
  s21_decimal b = {{0x0, 0x1, 0x0, 0x0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_less_max_scale) {
  s21_decimal a = {{0x1, 0x0, 0x0, 0x001C0000}};
  s21_decimal b = {{0x2, 0x0, 0x0, 0x001C0000}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_equal) {
  s21_decimal a = {{0x1, 0x2, 0x3, 0x00000000}};
  s21_decimal b = {{0x1, 0x2, 0x3, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_unequal) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xEFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_equal_different_scale) {
  s21_decimal a = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x001C0000}};
  s21_decimal b = {{0xA, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_equal_zeros) {
  s21_decimal a = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal b = {{0x0, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_equal_zeros_different_sign) {
  s21_decimal a = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal b = {{0x0, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_unequal_different_sign) {
  s21_decimal a = {{0x123, 0x123, 0x123, 0x80000000}};
  s21_decimal b = {{0x123, 0x123, 0x123, 0x0}};
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_unequal_different_scale) {
  s21_decimal a = {{0x123, 0x123, 0x123, 0x00130000}};
  s21_decimal b = {{0x123, 0x123, 0x123, 0x0}};
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

Suite *create_comparison_suite() {
  Suite *s = suite_create("Tests 21s_comparison :");
  TCase *tc_is_less = tcase_create("Is less");
  tcase_add_test(tc_is_less, test_is_less_less);
  tcase_add_test(tc_is_less, test_is_less_greater);
  tcase_add_test(tc_is_less, test_is_less_equal);
  tcase_add_test(tc_is_less, test_is_less_greater_different_signs);
  tcase_add_test(tc_is_less, test_is_less_less_different_scale);
  tcase_add_test(tc_is_less, test_is_less_equal_different_scale);
  tcase_add_test(tc_is_less,
                 test_is_less_greater_different_scale_both_negative);
  tcase_add_test(tc_is_less, test_is_less_less_both_negative);
  tcase_add_test(tc_is_less, test_is_less_less_one_zero);
  tcase_add_test(tc_is_less, test_is_less_equal_zeros_different_signs);
  tcase_add_test(tc_is_less, test_is_less_less_boundary_bits);
  tcase_add_test(tc_is_less, test_is_less_less_max_scale);

  TCase *tc_is_equal = tcase_create("Is equal");
  tcase_add_test(tc_is_equal, test_is_equal_equal);
  tcase_add_test(tc_is_equal, test_is_equal_unequal);
  tcase_add_test(tc_is_equal, test_is_equal_equal_different_scale);
  tcase_add_test(tc_is_equal, test_is_equal_equal_zeros);
  tcase_add_test(tc_is_equal, test_is_equal_equal_zeros_different_sign);
  tcase_add_test(tc_is_equal, test_is_equal_unequal_different_sign);
  tcase_add_test(tc_is_equal, test_is_equal_unequal_different_scale);

  suite_add_tcase(s, tc_is_less);
  suite_add_tcase(s, tc_is_equal);
  return s;
}
