#include "../tests_header.h"

START_TEST(test_memchr_char_at_boundary) {
  char *str = "Why I write tests?(";
  char c = 'e';
  s21_size_t n = 14;
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_char_outside_range) {
  char *str = "Why I write tests?(";
  char c = 'i';
  s21_size_t n = 8;
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_no_matching_char) {
  char *str = "Why I write tests?(";
  char c = 'T';
  s21_size_t n = strlen(str);
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_zero_range) {
  char *str = "Why I write tests?(";
  char c = 'W';
  s21_size_t n = 0;
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_null_character_in_range) {
  char *str = "Why I write tests?(";
  char c = '\0';
  s21_size_t n = strlen(str) + 1;
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_negative_value) {
  char str[] = {0, 1, -1};
  unsigned char c = 3;
  s21_size_t n = 3;
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_char_at_start) {
  char *str = "abc";
  char c = 'a';
  s21_size_t n = strlen(str);
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_char_at_end) {
  char *str = "abc  d";
  char c = 'd';
  s21_size_t n = strlen(str);
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

START_TEST(test_memchr_empty_string_no_match) {
  char *str = "";
  char c = 'a';
  s21_size_t n = 1;
  ck_assert_ptr_eq(memchr((void *)str, c, n), s21_memchr((void *)str, c, n));
}
END_TEST

Suite *create_memchr_suite() {
  Suite *s = suite_create("Tests s21_memchr O_o");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memchr_char_at_boundary);
  tcase_add_test(tc_core, test_memchr_char_outside_range);
  tcase_add_test(tc_core, test_memchr_no_matching_char);
  tcase_add_test(tc_core, test_memchr_zero_range);
  tcase_add_test(tc_core, test_memchr_null_character_in_range);
  tcase_add_test(tc_core, test_memchr_negative_value);
  tcase_add_test(tc_core, test_memchr_char_at_start);
  tcase_add_test(tc_core, test_memchr_char_at_end);
  tcase_add_test(tc_core, test_memchr_empty_string_no_match);
  suite_add_tcase(s, tc_core);
  return s;
}
