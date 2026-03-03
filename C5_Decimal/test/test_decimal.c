#include "test_decimal.h"

int main(void) {
  Suite* s;
  SRunner* runner;
  int number_failed;
  s = s21_add_suite();
  runner = srunner_create(s);
  s = s21_sub_suite();
  srunner_add_suite(runner, s);
  s = s21_mul_suite();
  srunner_add_suite(runner, s);
  s = s21_div_suite();
  srunner_add_suite(runner, s);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  s = create_other_suite();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  number_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  s = create_comparison_suite();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  number_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  s = int_conversion_suite();
  runner = srunner_create(s);
  s = float_conversion_suite();
  srunner_add_suite(runner, s);
  s = decimal_to_int_suite();
  srunner_add_suite(runner, s);
  s = decimal_to_float_suite();
  srunner_add_suite(runner, s);
  srunner_run_all(runner, CK_NORMAL);
  number_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}