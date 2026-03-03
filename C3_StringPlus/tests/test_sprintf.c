#include "../tests_header.h"

START_TEST(test_sprintf_basic_string) {
  char buffer1[100];
  char buffer2[100];
  char *str = "Hello dude!";

  int result1 = s21_sprintf(buffer1, "%s", str);
  int result2 = sprintf(buffer2, "%s", str);

  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_empty_string) {
  char buffer1[10];
  char buffer2[10];
  char *str = "";

  int result1 = s21_sprintf(buffer1, "%s", str);
  int result2 = sprintf(buffer2, "%s", str);

  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_symbols) {
  char buffer1[100];
  char buffer2[100];
  char c = 'H';
  char z = '\0';

  int res1 = s21_sprintf(buffer1, "%c %c", c, z);
  int res2 = sprintf(buffer2, "%c %c", c, z);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_multiple_types) {
  char buffer1[100];
  char buffer2[100];
  char c = 'W';
  char *str = "abrakada bra";
  int num = 9837476;

  int res1 = s21_sprintf(buffer1, "%c %d %s", c, num, str);
  int res2 = sprintf(buffer2, "%c %d %s", c, num, str);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_i_u_o_x_X_specs) {
  char buffer1[100];
  char buffer2[100];
  int num = 2724;
  unsigned int unsign = 4294967295U;

  int res1 = s21_sprintf(buffer1, "%i %u %o %x %X", num, unsign, num, num, num);
  int res2 = sprintf(buffer2, "%i %u %o %x %X", num, unsign, num, num, num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_pointer) {
  char buffer1[100];
  char buffer2[100];
  void *ptr = (void *)0x12345678;

  int res1 = s21_sprintf(buffer1, "%p", ptr);
  int res2 = sprintf(buffer2, "%p", ptr);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buffer1[100];
  char buffer2[100];

  int res1 = s21_sprintf(buffer1, "%%");
  int res2 = sprintf(buffer2, "%%");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_widths) {
  char buffer1[100];
  char buffer2[100];
  char *str = "ramamba";
  int num = 123;

  int res1 = s21_sprintf(buffer1, "%10s %5d %05d", str, num, num);
  int res2 = sprintf(buffer2, "%10s %5d %05d", str, num, num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_exponents) {
  char buffer1[100];
  char buffer2[100];
  float num = 12345.0f;

  int res1 = s21_sprintf(buffer1, "%E %e", num, num);
  int res2 = sprintf(buffer2, "%E %e", num, num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_floats_precision) {
  char buffer1[100];
  char buffer2[100];

  float num = 0.1233432f;

  int res1 = s21_sprintf(buffer1, "%.3f", num);
  int res2 = sprintf(buffer2, "%.3f", num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_n_spec) {
  char buffer1[100];
  char buffer2[100];
  int count1 = 0;
  int count2 = 0;

  int res1 = s21_sprintf(buffer1, "teststr%n", &count1);
  int res2 = sprintf(buffer2, "teststr%n", &count2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(count1, count2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_dynamic_width_precision) {
  char buffer1[100];
  char buffer2[100];
  int width = 10, precision = 2;
  float num = 3.14159f;

  int res1 = s21_sprintf(buffer1, "%*.*f", width, precision, num);
  int res2 = sprintf(buffer2, "%*.*f", width, precision, num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(test_sprintf_left_align) {
  char buffer1[100];
  char buffer2[100];
  char *str = "test";

  int res1 = s21_sprintf(buffer1, "%-10s", str);
  int res2 = sprintf(buffer2, "%-10s", str);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

Suite *create_sprintf_suite() {
  Suite *s = suite_create("Tests s21_sprintf!");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sprintf_basic_string);
  tcase_add_test(tc_core, test_sprintf_empty_string);
  tcase_add_test(tc_core, test_sprintf_symbols);
  tcase_add_test(tc_core, test_sprintf_multiple_types);
  tcase_add_test(tc_core, test_sprintf_i_u_o_x_X_specs);
  tcase_add_test(tc_core, test_sprintf_pointer);
  tcase_add_test(tc_core, test_sprintf_percent);
  tcase_add_test(tc_core, test_sprintf_widths);
  tcase_add_test(tc_core, test_sprintf_exponents);
  tcase_add_test(tc_core, test_sprintf_floats_precision);
  tcase_add_test(tc_core, test_sprintf_n_spec);
  tcase_add_test(tc_core, test_sprintf_dynamic_width_precision);
  tcase_add_test(tc_core, test_sprintf_left_align);
  suite_add_tcase(s, tc_core);
  return s;
}