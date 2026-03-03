#include "../tests_header.h"

START_TEST(test_sscanf_d_simple) {
  int a, b;
  const char* str = "123";
  int res1 = sscanf(str, "%d", &a);
  int res2 = s21_sscanf(str, "%d", &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_d_negative) {
  int a, b;
  const char* str = "-456";
  int res1 = s21_sscanf(str, "%d", &a);
  int res2 = sscanf(str, "%d", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_integer_i) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char* str = "123 0x1A 0777";

  int result1 = s21_sscanf(str, "%i %i %i", &a1, &b1, &c1);
  int result2 = sscanf(str, "%i %i %i", &a2, &b2, &c2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_hex) {
  unsigned int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  const char* str = "1A 0xFF";

  int result1 = s21_sscanf(str, "%x %X", &a1, &b1);
  int result2 = sscanf(str, "%x %X", &a2, &b2);

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_octal) {
  unsigned int a1 = 0, a2 = 0;
  const char* str = "776";

  int result1 = s21_sscanf(str, "%o", &a1);
  int result2 = sscanf(str, "%o", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_unsigned) {
  unsigned int a1 = 0, a2 = 0;
  const char* str = "4294967295";

  int result1 = s21_sscanf(str, "%u", &a1);
  int result2 = sscanf(str, "%u", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_pointer) {
  void *ptr1 = NULL, *ptr2 = NULL;
  const char* str = "0x1234abcd";

  int result1 = s21_sscanf(str, "%p", &ptr1);
  int result2 = sscanf(str, "%p", &ptr2);

  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_sscanf_char) {
  char a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  const char* str = "AB";

  int result1 = s21_sscanf(str, "%c%c", &a1, &b1);
  int result2 = sscanf(str, "%c%c", &a2, &b2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_string) {
  char str1[20] = {0}, str2[20] = {0};
  char str3[20] = {0}, str4[20] = {0};
  const char* input = "Hello World";

  int result1 = s21_sscanf(input, "%19s %19s", str1, str2);
  int result2 = sscanf(input, "%19s %19s", str3, str4);

  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str3);
  ck_assert_str_eq(str2, str4);
}
END_TEST

START_TEST(test_sscanf_float) {
  float f1 = 0.0, f2 = 0.0;
  const char* str = "3.14159";

  int result1 = s21_sscanf(str, "%f", &f1);
  int result2 = sscanf(str, "%f", &f2);

  ck_assert_int_eq(result1, result2);
  ck_assert(fabs(f1 - f2) < 0.00001);
}
END_TEST

START_TEST(test_sscanf_exponential) {
  float f1 = 0.0, f2 = 0.0;
  const char* str = "1.23e-4";

  int result1 = s21_sscanf(str, "%e", &f1);
  int result2 = sscanf(str, "%e", &f2);

  ck_assert_int_eq(result1, result2);
  ck_assert(fabs(f1 - f2) < 0.0000001);
}
END_TEST

START_TEST(test_sscanf_n) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, n1 = 0, n2 = 0;
  const char* str = "123 456";

  int result1 = s21_sscanf(str, "%d %d%n", &a1, &b1, &n1);
  int result2 = sscanf(str, "%d %d%n", &a2, &b2, &n2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sscanf_width) {
  char str1[10] = {0}, str2[10] = {0};
  char str3[10] = {0}, str4[10] = {0};
  const char* input = "HelloWorld";

  int result1 = s21_sscanf(input, "%5s%5s", str1, str2);
  int result2 = sscanf(input, "%5s%5s", str3, str4);

  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(str1, str3);
  ck_assert_str_eq(str2, str4);
}
END_TEST

START_TEST(test_sscanf_skip) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  const char* str = "123 456 789";

  int result1 = s21_sscanf(str, "%d %*d %d", &a1, &b1);
  int result2 = sscanf(str, "%d %*d %d", &a2, &b2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_length_modifiers) {
  short s1 = 0, s2 = 0;
  long l1 = 0, l2 = 0;
  unsigned short us1 = 0, us2 = 0;
  unsigned long ul1 = 0, ul2 = 0;
  const char* str = "32767 2147483647 65535 4294967295";

  int result1 = s21_sscanf(str, "%hd %ld %hu %lu", &s1, &l1, &us1, &ul1);
  int result2 = sscanf(str, "%hd %ld %hu %lu", &s2, &l2, &us2, &ul2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(s1, s2);
  ck_assert_int_eq(l1, l2);
  ck_assert_uint_eq(us1, us2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(test_sscanf_percent) {
  int a1 = 0, a2 = 0;
  const char* str = "100%";

  int result1 = s21_sscanf(str, "%d%%", &a1);
  int result2 = sscanf(str, "%d%%", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_literal_match) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  const char* str = "Value: 123, Count: 456";

  int result1 = s21_sscanf(str, "Value: %d, Count: %d", &a1, &b1);
  int result2 = sscanf(str, "Value: %d, Count: %d", &a2, &b2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_float_scientific) {
  float f1 = 0.0, f2 = 0.0;
  long double d1 = 0.0, d2 = 0.0;
  const char* str = "1.23e+4 6.78E-3";

  int result1 = s21_sscanf(str, "%f %Lf", &f1, &d1);
  int result2 = sscanf(str, "%f %Lf", &f2, &d2);

  ck_assert_int_eq(result1, result2);
  ck_assert(fabs(f1 - f2) < 0.1);
  ck_assert(fabsl(d1 - d2) < 0.0001L);
}
END_TEST

START_TEST(test_sscanf_width_limitation) {
  int a1 = 0, a2 = 0;
  const char* str = "123456";

  int result1 = s21_sscanf(str, "%3d", &a1);
  int result2 = sscanf(str, "%3d", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_no_match) {
  int a1 = 0, a2 = 0;
  const char* str = "abc";

  int result1 = s21_sscanf(str, "%d", &a1);
  int result2 = sscanf(str, "%d", &a2);

  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_multiple_chars) {
  char chars1[10] = {0}, chars2[10] = {0};
  const char* str = "abcdef";

  int result1 = s21_sscanf(str, "%3c", chars1);
  int result2 = sscanf(str, "%3c", chars2);

  ck_assert_int_eq(result1, result2);
  ck_assert_mem_eq(chars1, chars2, 3);
}
END_TEST

Suite* create_sscanf_suite() {
  Suite* s = suite_create("Tests s21_sscanf");
  TCase* tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sscanf_d_simple);
  tcase_add_test(tc_core, test_sscanf_d_negative);
  tcase_add_test(tc_core, test_sscanf_integer_i);
  tcase_add_test(tc_core, test_sscanf_hex);
  tcase_add_test(tc_core, test_sscanf_octal);
  tcase_add_test(tc_core, test_sscanf_unsigned);
  tcase_add_test(tc_core, test_sscanf_pointer);
  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_string);
  tcase_add_test(tc_core, test_sscanf_float);
  tcase_add_test(tc_core, test_sscanf_exponential);
  tcase_add_test(tc_core, test_sscanf_n);
  tcase_add_test(tc_core, test_sscanf_width);
  tcase_add_test(tc_core, test_sscanf_skip);
  tcase_add_test(tc_core, test_sscanf_length_modifiers);
  tcase_add_test(tc_core, test_sscanf_percent);
  tcase_add_test(tc_core, test_sscanf_literal_match);
  tcase_add_test(tc_core, test_sscanf_float_scientific);
  tcase_add_test(tc_core, test_sscanf_width_limitation);
  tcase_add_test(tc_core, test_sscanf_no_match);
  tcase_add_test(tc_core, test_sscanf_multiple_chars);
  suite_add_tcase(s, tc_core);
  return s;
}