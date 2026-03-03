#include "../tests_header.h"

START_TEST(test_strncmp_basic_equal) {
  char *str1 = "hello";
  char *str2 = "hello";
  s21_size_t n = 5;
  ck_assert_int_eq(strncmp(str1, str2, n), s21_strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_basic_not_equal) {
  char *str1 = "hello";
  char *str2 = "world";
  s21_size_t n = 5;
  ck_assert_int_eq(strncmp(str1, str2, n), s21_strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_partial_match) {
  char *str1 = "hello";
  char *str2 = "help";
  s21_size_t n = 4;
  ck_assert_int_eq(strncmp(str1, str2, n), s21_strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_n_zero) {
  char *str1 = "hello";
  char *str2 = "world";
  s21_size_t n = 0;
  ck_assert_int_eq(strncmp(str1, str2, n), s21_strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_one_empty) {
  char *str1 = "";
  char *str2 = "nonempty";
  s21_size_t n = 5;
  ck_assert_int_eq(strncmp(str1, str2, n), s21_strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_both_empty) {
  char *str1 = "";
  char *str2 = "";
  s21_size_t n = 5;
  ck_assert_int_eq(strncmp(str1, str2, n), s21_strncmp(str1, str2, n));
}
END_TEST

Suite *create_strncmp_suite() {
  Suite *s = suite_create("Tests s21_strncmp :)");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strncmp_basic_equal);
  tcase_add_test(tc_core, test_strncmp_basic_not_equal);
  tcase_add_test(tc_core, test_strncmp_partial_match);
  tcase_add_test(tc_core, test_strncmp_n_zero);
  tcase_add_test(tc_core, test_strncmp_one_empty);
  tcase_add_test(tc_core, test_strncmp_both_empty);
  suite_add_tcase(s, tc_core);
  return s;
}