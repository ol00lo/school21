#include "../tests_header.h"

START_TEST(test_strpbrk_sign_search_in_line) {
  char *str = "123456789";
  char *str_search = "5";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_sign_search_in_start) {
  char *str = "123456789";
  char *str_search = "1";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_sign_search_in_end) {
  char *str = "abcdefgh";
  char *str_search = "h";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_several_signs_search_in_line) {
  char *str = "abcdefgh dc";
  char *str_search = "dc";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_no_matches) {
  char *str = "ABCDEFgh";
  char *str_search = "abc";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_line_and_search_sing_space) {
  char *str = " ";
  char *str_search = " ";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_signs_search_empty) {
  char *str = "123456789";
  char *str_search = "";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_line_empty) {
  char *str = "";
  char *str_search = "123";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

START_TEST(test_strpbrk_both_empty) {
  char *str = "";
  char *str_search = "";
  ck_assert_ptr_eq(strpbrk(str, str_search), s21_strpbrk(str, str_search));
}
END_TEST

Suite *create_strpbrk_suite() {
  Suite *s = suite_create("Tests s21_strpbrk O_o");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strpbrk_sign_search_in_line);
  tcase_add_test(tc_core, test_strpbrk_sign_search_in_start);
  tcase_add_test(tc_core, test_strpbrk_sign_search_in_end);
  tcase_add_test(tc_core, test_strpbrk_several_signs_search_in_line);
  tcase_add_test(tc_core, test_strpbrk_no_matches);
  tcase_add_test(tc_core, test_strpbrk_line_and_search_sing_space);
  tcase_add_test(tc_core, test_strpbrk_signs_search_empty);
  tcase_add_test(tc_core, test_strpbrk_line_empty);
  tcase_add_test(tc_core, test_strpbrk_both_empty);
  suite_add_tcase(s, tc_core);
  return s;
}
