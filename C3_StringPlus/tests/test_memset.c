#include "../tests_header.h"

START_TEST(test_memset_zero_fill) {
  char buffer1[10];
  char buffer2[10];

  s21_memset(buffer1, 0, 10);
  memset(buffer2, 0, 10);

  ck_assert_mem_eq(buffer1, buffer2, 10);
}
END_TEST

START_TEST(test_memset_char_fill) {
  char buffer1[10];
  char buffer2[10];

  s21_memset(buffer1, 'A', 10);
  memset(buffer2, 'A', 10);

  ck_assert_mem_eq(buffer1, buffer2, 10);
}
END_TEST

START_TEST(test_memset_n_zero) {
  char buffer1[10] = "test";

  char *result1 = s21_memset(buffer1, 'X', 0);

  ck_assert_ptr_eq(result1, buffer1);
  ck_assert_str_eq(buffer1, "test");
}
END_TEST

START_TEST(test_memset_partial_fill) {
  char buffer1[10] = "testtest";
  char buffer2[10] = "testtest";

  s21_memset(buffer1, 'X', 4);
  memset(buffer2, 'X', 4);

  ck_assert_mem_eq(buffer1, buffer2, 10);
}
END_TEST

START_TEST(test_memset_large_c) {
  char buffer1[10];
  char buffer2[10];

  s21_memset(buffer1, 44, 10);
  memset(buffer2, 44, 10);
  ck_assert_mem_eq(buffer1, buffer2, 10);
}
END_TEST

START_TEST(test_memset_negative_c) {
  char buffer1[10];
  char buffer2[10];

  s21_memset(buffer1, -1, 10);
  memset(buffer2, -1, 10);

  ck_assert_mem_eq(buffer1, buffer2, 10);
}
END_TEST

START_TEST(test_memset_return_value) {
  char buffer[10];
  char *ret = (char *)s21_memset(buffer, 0, 10);
  ck_assert_ptr_eq(ret, buffer);
}
END_TEST

Suite *create_memset_suite() {
  Suite *s = suite_create("Tests s21_memset :)");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memset_zero_fill);
  tcase_add_test(tc_core, test_memset_char_fill);
  tcase_add_test(tc_core, test_memset_n_zero);
  tcase_add_test(tc_core, test_memset_partial_fill);
  tcase_add_test(tc_core, test_memset_large_c);
  tcase_add_test(tc_core, test_memset_negative_c);
  tcase_add_test(tc_core, test_memset_return_value);

  suite_add_tcase(s, tc_core);
  return s;
}