#include "../tests_header.h"

START_TEST(test_strerror_107_code_errors) {
  for (int i = 1; i < 107; i++) ck_assert_str_eq(strerror(i), s21_strerror(i));
}
END_TEST

START_TEST(test_strerror_name_error) {
  int name = ELOOP;
  ck_assert_str_eq(strerror(name), s21_strerror(name));
}
END_TEST

Suite *create_strerror_suite() {
  Suite *s = suite_create("Tests s21_strerror O_o");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strerror_107_code_errors);
  tcase_add_test(tc_core, test_strerror_name_error);
  suite_add_tcase(s, tc_core);
  return s;
}
