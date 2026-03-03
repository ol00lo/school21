#include "../tests_header.h"

START_TEST(test_insert_at_start) {
  char *src = "Src string";
  char *str = "Str string";
  s21_size_t index = 0;
  char *result = s21_insert(src, str, index);
  char *expected = "Str stringSrc string";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_at_middle) {
  char *src = "vljneskj";
  char *str = "1234";
  s21_size_t index = 4;
  char *result = s21_insert(src, str, index);
  char *expected = "vljn1234eskj";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_at_end) {
  char *src = "12345";
  char *str = "67890";
  s21_size_t index = 5;
  char *result = s21_insert(src, str, index);
  char *expected = "1234567890";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_index_out_of_bounds) {
  char *src = "12345";
  char *str = "54321";
  s21_size_t index = 10;

  char *result = s21_insert(src, str, index);
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_NULL_arguments) {
  char *result = s21_insert(S21_NULL, "test", 0);
  ck_assert_ptr_eq(result, S21_NULL);

  result = s21_insert("test", S21_NULL, 0);
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_empty_str_string) {
  char *src = "src string";
  char *str = "";
  s21_size_t index = 2;

  char *result = s21_insert(src, str, index);
  char *expected = "src string";
  ck_assert_str_eq(result, expected);
}
END_TEST

Suite *create_insert_suite() {
  Suite *s = suite_create("Tests s21_insert :)");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_insert_at_start);
  tcase_add_test(tc_core, test_insert_at_middle);
  tcase_add_test(tc_core, test_insert_at_end);
  tcase_add_test(tc_core, test_insert_index_out_of_bounds);
  tcase_add_test(tc_core, test_insert_NULL_arguments);
  tcase_add_test(tc_core, test_insert_empty_str_string);

  suite_add_tcase(s, tc_core);
  return s;
}