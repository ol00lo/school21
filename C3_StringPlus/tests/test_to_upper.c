#include "../tests_header.h"

START_TEST(test_to_upper_normal_string) {
  char str[] = "Hello, world!";
  char* str2 = s21_to_upper(str);
  ck_assert_str_eq("HELLO, WORLD!", str2);
  free(str2);
}
END_TEST

START_TEST(test_to_upper_all_upper) {
  char str[] = "AAAAAAVBDFSDADS";
  char* str2 = s21_to_upper(str);
  ck_assert_str_eq("AAAAAAVBDFSDADS", str2);
  free(str2);
}
END_TEST

START_TEST(test_to_upper_empty_string) {
  char str[] = "";
  char* result = (char*)s21_to_upper(str);

  ck_assert_ptr_eq(S21_NULL, result);
  free(result);
}
END_TEST

START_TEST(test_to_upper_no_letter) {
  char str[] = "!$&?";
  char* str2 = s21_to_upper(str);
  ck_assert_str_eq("!$&?", str2);
  free(str2);
}
END_TEST

Suite* create_to_upper_suite(void) {
  Suite* s = suite_create("Tests s21_to_upper O_o");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_upper_normal_string);
  tcase_add_test(tc_core, test_to_upper_all_upper);
  tcase_add_test(tc_core, test_to_upper_empty_string);
  tcase_add_test(tc_core, test_to_upper_no_letter);
  suite_add_tcase(s, tc_core);
  return s;
}