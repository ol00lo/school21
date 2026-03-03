#include "../tests_header.h"

START_TEST(test_strstr_normal_string) {
  char str1[] = "Hello, world!";
  char str2[] = "world";
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  char str1[] = "Hello, world!";
  char str2[] = "";
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST
START_TEST(test_strstr_empty_string) {
  char str1[] = "";
  char str2[] = "AV";
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(test_strstr_a_lot_strings_in) {
  char str1[] = "BAABABAABAABAAB";
  char str2[] = "AAB";
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(test_strstr_not_in_string) {
  char str1[] = "Hello,world!";
  char str2[] = "Boys";
  ck_assert_ptr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

Suite* create_strstr_suite(void) {
  Suite* s = suite_create("Tests s21_strstr O_o");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strstr_normal_string);
  tcase_add_test(tc_core, test_strstr_empty_needle);
  tcase_add_test(tc_core, test_strstr_empty_string);
  tcase_add_test(tc_core, test_strstr_a_lot_strings_in);
  tcase_add_test(tc_core, test_strstr_not_in_string);
  suite_add_tcase(s, tc_core);
  return s;
}