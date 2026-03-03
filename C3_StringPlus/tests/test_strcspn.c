#include "../tests_header.h"

START_TEST(test_strcspn_single_char_in_middle) {
  char *str = "abcd efgh";
  char *delimiter = " ";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_single_char_at_start) {
  char *str = " abcdefgh";
  char *delimiter = " ";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_single_char_at_end) {
  char *str = "abcdefgh ";
  char *delimiter = " ";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_multiple_delimiters_in_string) {
  char *str = "ab.cd, efgh";
  char *delimiter = ", .";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_string_with_only_delimiters) {
  char *str = "7777770777";
  char *delimiter = "70";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_no_occurrence) {
  char *str = "i rad testirovat etu funkciyu";
  char *delimiter = "=+-I";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_empty_input_string) {
  char *str = "";
  char *delimiter = "123";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_empty_delimiters) {
  char *str = "321";
  char *delimiter = "";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

START_TEST(test_strcspn_single_char_match) {
  char *str = "?";
  char *delimiter = "?";
  ck_assert_uint_eq(strcspn(str, delimiter), s21_strcspn(str, delimiter));
}
END_TEST

Suite *create_strcspn_suite() {
  Suite *s = suite_create("Tests s21_strcspn O_o");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strcspn_single_char_in_middle);
  tcase_add_test(tc_core, test_strcspn_single_char_at_start);
  tcase_add_test(tc_core, test_strcspn_single_char_at_end);
  tcase_add_test(tc_core, test_strcspn_multiple_delimiters_in_string);
  tcase_add_test(tc_core, test_strcspn_string_with_only_delimiters);
  tcase_add_test(tc_core, test_strcspn_no_occurrence);
  tcase_add_test(tc_core, test_strcspn_empty_input_string);
  tcase_add_test(tc_core, test_strcspn_empty_delimiters);
  tcase_add_test(tc_core, test_strcspn_single_char_match);
  suite_add_tcase(s, tc_core);
  return s;
}
