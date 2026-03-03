#include "../tests_header.h"

START_TEST(test_trim_basic) {
  char *src = "###hello###";
  char *trim = "#";
  char *result = s21_trim(src, trim);
  char *expected = "hello";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_spaces) {
  char *src = "   hello   ";
  char *trim = " ";
  char *result = s21_trim(src, trim);
  char *expected = "hello";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_multiple_chars) {
  char *src = "xyzabczyx";
  char *trim = "xyz";
  char *result = s21_trim(src, trim);
  char *expected = "abc";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_entirely_trimmed) {
  char *src = "!!!";
  char *trim = "!";
  char *result = s21_trim(src, trim);
  char *expected = "";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_empty_src) {
  char *src = "";
  char *trim = "abc";
  char *result = s21_trim(src, trim);
  char *expected = "";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_null_arguments) {
  char *result = s21_trim(S21_NULL, "test");
  ck_assert_ptr_eq(result, S21_NULL);

  result = s21_trim("test", S21_NULL);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "test");
  free(result);
}
END_TEST

START_TEST(test_trim_nothing_to_trim) {
  char *src = "hello";
  char *trim = "xyz";
  char *result = s21_trim(src, trim);
  char *expected = "hello";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

Suite *create_trim_suite() {
  Suite *s = suite_create("s21_trim :))");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_trim_basic);
  tcase_add_test(tc, test_trim_spaces);
  tcase_add_test(tc, test_trim_multiple_chars);
  tcase_add_test(tc, test_trim_entirely_trimmed);
  tcase_add_test(tc, test_trim_empty_src);
  tcase_add_test(tc, test_trim_null_arguments);
  tcase_add_test(tc, test_trim_nothing_to_trim);

  suite_add_tcase(s, tc);
  return s;
}