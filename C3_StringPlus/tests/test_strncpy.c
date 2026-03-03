#include "../tests_header.h"

START_TEST(test_strncpy_src_shorter_than_n) {
  char dest1[20];
  char dest2[20];

  const char *src = "abc";
  s21_size_t n = 6;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(test_strncpy_src_is_equal_to_n) {
  char dest1[20];
  char dest2[20];

  const char *src = "abcdef";
  s21_size_t n = 6;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(test_strncpy_n_is_equal_to_0) {
  char dest1[20];
  char dest2[20];

  for (int i = 0; i < 20; i++) {
    dest1[i] = dest2[i] = 'F';
  }

  const char *src = "abaslaslcc";
  s21_size_t n = 0;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(test_strncpy_src_longer_than_n) {
  char dest1[20];
  char dest2[20];

  const char *src = "hello world";
  s21_size_t n = 5;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(test_strncpy_src_empty) {
  char dest1[20];
  char dest2[20];

  const char *src = "";
  s21_size_t n = 10;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(test_strncpy_return_value) {
  char dest[20] = {0};
  const char *src = "hello";

  char *result = s21_strncpy(dest, src, 10);
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_strncpy_n_greater_than_src_length) {
  char dest1[20];
  char dest2[20];

  const char *src = "abc";
  s21_size_t n = 10;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(test_strncpy_src_dest_overlap) {
  char src[20] = "hello world";
  char dest1[20] = "hello world";
  char dest2[20] = "hello world";

  s21_size_t n = 5;

  strncpy(dest1, src, n);
  s21_strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

Suite *create_strncpy_suite() {
  Suite *s = suite_create("Tests s21_strncpy :)");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncpy_src_shorter_than_n);
  tcase_add_test(tc_core, test_strncpy_src_is_equal_to_n);
  tcase_add_test(tc_core, test_strncpy_n_is_equal_to_0);
  tcase_add_test(tc_core, test_strncpy_src_longer_than_n);
  tcase_add_test(tc_core, test_strncpy_src_empty);
  tcase_add_test(tc_core, test_strncpy_return_value);
  tcase_add_test(tc_core, test_strncpy_n_greater_than_src_length);
  tcase_add_test(tc_core, test_strncpy_src_dest_overlap);

  suite_add_tcase(s, tc_core);
  return s;
}