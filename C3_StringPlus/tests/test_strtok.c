#include "../tests_header.h"

START_TEST(test_strtok_separator_in_line) {
  char str1[] = "1 2 3";
  char str2[] = "1 2 3";
  char *str3 = " ";
  for (int i = 0; i < 3; i++)
    ck_assert_str_eq(strtok(i == 0 ? str1 : S21_NULL, str3),
                     s21_strtok(i == 0 ? str2 : S21_NULL, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_separator_in_a_row_in_line) {
  char str1[] = "one---two--three-four";
  char str2[] = "one---two--three-four";
  char *str3 = "-";
  for (int i = 0; i < 4; i++)
    ck_assert_str_eq(strtok(i == 0 ? str1 : S21_NULL, str3),
                     s21_strtok(i == 0 ? str2 : S21_NULL, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_separator_in_start) {
  char str1[] = "-one-two-three";
  char str2[] = "-one-two-three";
  char *str3 = "-";
  for (int i = 0; i < 3; i++)
    ck_assert_str_eq(strtok(i == 0 ? str1 : S21_NULL, str3),
                     s21_strtok(i == 0 ? str2 : S21_NULL, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_separator_in_end) {
  char str1[] = "onetwothree-";
  char str2[] = "onetwothree-";
  char *str3 = "-";
  ck_assert_str_eq(strtok(str1, str3), s21_strtok(str2, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_no_separators_in_line) {
  char str1[] = "OneTwoThree";
  char str2[] = "OneTwoThree";
  char *str3 = " ,";
  ck_assert_str_eq(strtok(str1, str3), s21_strtok(str2, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_separators_in_line) {
  char str1[] = "-,.One+.,Two.Three.";
  char str2[] = "-,.One+.,Two.Three.";
  char *str3 = ".,-+";
  for (int i = 0; i < 3; i++)
    ck_assert_str_eq(strtok(i == 0 ? str1 : S21_NULL, str3),
                     s21_strtok(i == 0 ? str2 : S21_NULL, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_empty_separators) {
  char str1[] = "One Two Three.";
  char str2[] = "One Two Three.";
  char *str3 = "";
  ck_assert_str_eq(strtok(str1, str3), s21_strtok(str2, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_empty_line) {
  char str1[] = "";
  char str2[] = "";
  char *str3 = "123";
  ck_assert_ptr_eq(strtok(str1, str3), s21_strtok(str2, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_both_empty) {
  char str1[] = "";
  char str2[] = "";
  char *str3 = "";
  ck_assert_ptr_eq(strtok(str1, str3), s21_strtok(str2, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

START_TEST(test_strtok_pass_different_lines) {
  char str1[] = "who?are?you";
  char str2[] = "who?are?you";
  char str_next1[] = "403";
  char str_next2[] = "403";
  char *str3 = "?";
  ck_assert_str_eq(strtok(str1, str3), s21_strtok(str2, str3));
  ck_assert_str_eq(strtok(str_next1, str3), s21_strtok(str_next2, str3));
  ck_assert_ptr_eq(strtok(S21_NULL, str3), s21_strtok(S21_NULL, str3));
}
END_TEST

Suite *create_strtok_suite() {
  Suite *s = suite_create("Tests s21_strtok O_o");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strtok_separator_in_line);
  tcase_add_test(tc_core, test_strtok_separator_in_a_row_in_line);
  tcase_add_test(tc_core, test_strtok_separator_in_start);
  tcase_add_test(tc_core, test_strtok_separator_in_end);
  tcase_add_test(tc_core, test_strtok_no_separators_in_line);
  tcase_add_test(tc_core, test_strtok_separators_in_line);
  tcase_add_test(tc_core, test_strtok_empty_separators);
  tcase_add_test(tc_core, test_strtok_empty_line);
  tcase_add_test(tc_core, test_strtok_both_empty);
  tcase_add_test(tc_core, test_strtok_pass_different_lines);

  suite_add_tcase(s, tc_core);
  return s;
}
