#include "../tests_header.h"

START_TEST(test_strchr_first_occurrence_in_line) {
  char *str = "Hello World!";
  char c = 'l';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(test_strchr_char_at_start) {
  char *str = "Alpha";
  char c = 'A';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(test_strchr_char_at_end) {
  char *str = "Beta";
  char c = 'a';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(test_strchr_no_matching_char) {
  char *str = "Gamma";
  char c = 'z';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(test_strchr_empty_string) {
  char *str = "";
  char c = 'X';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(test_strchr_null_character) {
  char *str = "Delta\0Extra";
  char c = '\0';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(test_strchr_large_input) {
  char largeStr[1024];
  memset(largeStr, 'a', sizeof(largeStr) - 1);
  largeStr[sizeof(largeStr) - 1] = '\0';
  char c = 'b';
  largeStr[sizeof(largeStr) - 2] = c;
  ck_assert_ptr_eq(strchr(largeStr, c), s21_strchr(largeStr, c));
}
END_TEST

START_TEST(test_strchr_multiple_matches) {
  char *str = "Mississippi";
  char c = 'i';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

START_TEST(test_strchr_single_character) {
  char *str = "Z";
  char c = 'Z';
  ck_assert_ptr_eq(strchr(str, c), s21_strchr(str, c));
}
END_TEST

Suite *create_strchr_suite() {
  Suite *s = suite_create("Tests s21_strchr O_o");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strchr_first_occurrence_in_line);
  tcase_add_test(tc_core, test_strchr_char_at_start);
  tcase_add_test(tc_core, test_strchr_char_at_end);
  tcase_add_test(tc_core, test_strchr_no_matching_char);
  tcase_add_test(tc_core, test_strchr_empty_string);
  tcase_add_test(tc_core, test_strchr_null_character);
  tcase_add_test(tc_core, test_strchr_large_input);
  tcase_add_test(tc_core, test_strchr_multiple_matches);
  tcase_add_test(tc_core, test_strchr_single_character);
  suite_add_tcase(s, tc_core);
  return s;
}
