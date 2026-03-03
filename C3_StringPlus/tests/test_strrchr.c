#include "../tests_header.h"

START_TEST(test_strrchr_normal_string) {
  char str[] = "Hello, world!";
  int c = 'l';
  ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_empty_string) {
  char str[] = "";
  int c = 'a';
  ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_not_in_string) {
  char str[] = "ABGFA";
  int c = 'L';
  ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));
}
END_TEST

Suite* create_strrchr_suite(void) {
  Suite* s = suite_create("Tests s21_strrchr O_o");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strrchr_normal_string);
  tcase_add_test(tc_core, test_strrchr_empty_string);
  tcase_add_test(tc_core, test_strrchr_not_in_string);
  suite_add_tcase(s, tc_core);
  return s;
}