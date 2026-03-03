#include "../tests_header.h"

START_TEST(test_memcmp_same_strings) {
  char str1[] = "Example string";
  char str2[] = "Example string";
  s21_size_t n = strlen(str1);
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_different_strings) {
  char str1[] = "String one";
  char str2[] = "Different string";
  size_t n = strlen(str2);
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_empty_strings) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t n = strlen(str1);
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_different_lengths) {
  char str1[] = "String";
  char str2[] = "String but longer";
  s21_size_t n = strlen(str2);
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_strings_different_but_equal_in_range) {
  char str1[] = "Equal";
  char str2[] = "Equal but no more";
  s21_size_t n = strlen(str1);
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}

START_TEST(test_memcmp_long_buffers) {
  char buffer1[1024];
  char buffer2[1024];
  memset(buffer1, 'X', sizeof(buffer1));
  memset(buffer2, 'X', sizeof(buffer2));
  s21_size_t n = sizeof(buffer1);
  ck_assert_int_eq(memcmp(buffer1, buffer2, n),
                   s21_memcmp(buffer1, buffer2, n));
}
END_TEST

START_TEST(test_memcmp_unaligned_memory) {
  struct TestStruct {
    char data[10];
  };
  struct TestStruct ts1 = {.data = {"Unaligned\0"}};
  struct TestStruct ts2 = {.data = {"Data\0\0\0\0\0"}};
  s21_size_t n = sizeof(ts1.data);
  ck_assert_int_eq(memcmp(&ts1.data, &ts2.data, n),
                   s21_memcmp(&ts1.data, &ts2.data, n));
}
END_TEST

START_TEST(test_memcmp_bytes_only_difference) {
  char str1[] = {0x01, 0x02, 0x03};
  char str2[] = {0x01, 0x02, 0x04};
  s21_size_t n = sizeof(str1);
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_zero_length) {
  char str1[] = "Non-empty";
  char str2[] = "Other non-empty";
  s21_size_t n = 0;
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_null_terminated_strings) {
  char str1[] = "This is a test";
  char str2[] = "This is a test another";
  s21_size_t n = strlen(str1) + 1;
  ck_assert_int_eq(memcmp(str1, str2, n), s21_memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_aligned_memory) {
  char aligned_buffer1[16] __attribute__((aligned(16)));
  char aligned_buffer2[16] __attribute__((aligned(16)));
  memcpy(aligned_buffer1, "Aligned Buffer One", sizeof(aligned_buffer1));
  memcpy(aligned_buffer2, "Aligned Buffer Two", sizeof(aligned_buffer2));
  s21_size_t n = sizeof(aligned_buffer1);
  ck_assert_int_eq(memcmp(aligned_buffer1, aligned_buffer2, n),
                   s21_memcmp(aligned_buffer1, aligned_buffer2, n));
}
END_TEST

Suite *create_memcmp_suite(void) {
  Suite *s = suite_create("Tests s21_memcmp O_o");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcmp_same_strings);
  tcase_add_test(tc_core, test_memcmp_different_strings);
  tcase_add_test(tc_core, test_memcmp_empty_strings);
  tcase_add_test(tc_core, test_memcmp_different_lengths);
  tcase_add_test(tc_core, test_memcmp_strings_different_but_equal_in_range);
  tcase_add_test(tc_core, test_memcmp_long_buffers);
  tcase_add_test(tc_core, test_memcmp_unaligned_memory);
  tcase_add_test(tc_core, test_memcmp_bytes_only_difference);
  tcase_add_test(tc_core, test_memcmp_zero_length);
  tcase_add_test(tc_core, test_memcmp_null_terminated_strings);
  tcase_add_test(tc_core, test_memcmp_aligned_memory);
  suite_add_tcase(s, tc_core);
  return s;
}
