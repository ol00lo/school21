#include "../tests_header.h"

START_TEST(test_memcpy_normal_string) {
  char str1[] = "Hello, world";
  s21_size_t n = 5;
  char dest1[n + 1];
  char dest2[n + 1];
  memcpy(dest1, str1, n);
  s21_memcpy(dest2, str1, n);
  for (s21_size_t i = 0; i < n; ++i) {
    ck_assert_int_eq(dest1[i], dest2[i]);
  }
}
END_TEST

START_TEST(test_memcpy_empty_string) {
  char str1[] = "";
  s21_size_t n = 0;
  char dest1[1] = {0};
  char dest2[1] = {0};
  memcpy(dest1, str1, n);
  s21_memcpy(dest2, str1, n);
  ck_assert_int_eq(dest1[n], dest2[n]);
}
END_TEST

START_TEST(test_memcpy_zero_n) {
  char str1[] = "Hello, boy!";
  s21_size_t n = 0;
  char dest1[1] = {0};
  char dest2[1] = {0};
  memcpy(dest1, str1, n);
  s21_memcpy(dest2, str1, n);
  ck_assert_int_eq(dest1[n], dest2[n]);
}
END_TEST

Suite* create_memcpy_suite(void) {
  Suite* s = suite_create("Tests s21_memcpy O_o");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcpy_normal_string);
  tcase_add_test(tc_core, test_memcpy_empty_string);
  tcase_add_test(tc_core, test_memcpy_zero_n);
  suite_add_tcase(s, tc_core);
  return s;
}