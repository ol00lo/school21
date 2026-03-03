#include "../tests_header.h"

START_TEST(test_normal_case) {
  char dest1[100] = "Test: ";
  char dest2[100] = "Test: ";
  const char *src = "Hello, World!";
  s21_size_t n = 5;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_append_full_src) {
  char dest1[100] = "Test: ";
  char dest2[100] = "Test: ";
  const char *src = "abc";
  s21_size_t n = 10;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_n_is_zero) {
  char dest1[100] = "Test: ";
  char dest2[100] = "Test: ";
  const char *src = "Hello";
  s21_size_t n = 0;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_src_is_empty) {
  char dest1[100] = "Test: ";
  char dest2[100] = "Test: ";
  const char *src = "";
  s21_size_t n = 10;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_dest_is_empty) {
  char dest1[100] = "";
  char dest2[100] = "";
  const char *src = "Data";
  s21_size_t n = 4;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_n_greater_than_src_len) {
  char dest1[100] = "";
  char dest2[100] = "";
  const char *src = "Short";
  s21_size_t n = 20;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_return_value) {
  char dest1[100] = "Start";
  char *ret = s21_strncat(dest1, "End", 3);
  ck_assert_ptr_eq(ret, dest1);
}
END_TEST

Suite *create_strncat_suite() {
  Suite *s = suite_create("Tests s21_strncat :)");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_normal_case);
  tcase_add_test(tc_core, test_append_full_src);
  tcase_add_test(tc_core, test_n_is_zero);
  tcase_add_test(tc_core, test_src_is_empty);
  tcase_add_test(tc_core, test_dest_is_empty);
  tcase_add_test(tc_core, test_n_greater_than_src_len);
  tcase_add_test(tc_core, test_return_value);

  suite_add_tcase(s, tc_core);
  return s;
}