#include "../tests_header.h"

START_TEST(test_strlen_normal_string) {
  char str[] = "Hello, world!";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(test_strlen_empty_string) {
  char str[] = "";
  ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

Suite* create_strlen_suite(void) {
  Suite* s = suite_create("Tests s21_strlen O_o");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strlen_normal_string);
  tcase_add_test(tc_core, test_strlen_empty_string);
  suite_add_tcase(s, tc_core);
  return s;
}