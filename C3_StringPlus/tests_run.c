#include "tests_header.h"

void run_your_suite_tests(Suite* s, int* number_failed);

int main() {
  int number_failed = 0;
  Suite* memchr_suite = create_memchr_suite();
  Suite* memcmp_suite = create_memcmp_suite();
  Suite* strchr_suite = create_strchr_suite();
  Suite* strcspn_suite = create_strcspn_suite();
  Suite* strerror_suite = create_strerror_suite();
  Suite* strpbrk_suite = create_strpbrk_suite();
  Suite* strtok_suite = create_strtok_suite();
  Suite* strncat_suite = create_strncat_suite();
  Suite* strncmp_suite = create_strncmp_suite();
  Suite* memset_suite = create_memset_suite();
  Suite* strncpy_suite = create_strncpy_suite();
  Suite* insert_suite = create_insert_suite();
  Suite* trim_suite = create_trim_suite();
  Suite* memcpy_suite = create_memcpy_suite();
  Suite* strlen_suite = create_strlen_suite();
  Suite* strrchr_suite = create_strrchr_suite();
  Suite* strstr_suite = create_strstr_suite();
  Suite* to_upper_suite = create_to_upper_suite();
  Suite* to_lower_suite = create_to_lower_suite();
  Suite* sscanf_suite = create_sscanf_suite();
  Suite* sprintf_suite = create_sprintf_suite();

  run_your_suite_tests(memchr_suite, &number_failed);
  run_your_suite_tests(memcmp_suite, &number_failed);
  run_your_suite_tests(strchr_suite, &number_failed);
  run_your_suite_tests(strcspn_suite, &number_failed);
  run_your_suite_tests(strerror_suite, &number_failed);
  run_your_suite_tests(strpbrk_suite, &number_failed);
  run_your_suite_tests(strtok_suite, &number_failed);
  run_your_suite_tests(strncat_suite, &number_failed);
  run_your_suite_tests(strncmp_suite, &number_failed);
  run_your_suite_tests(memset_suite, &number_failed);
  run_your_suite_tests(strncpy_suite, &number_failed);
  run_your_suite_tests(insert_suite, &number_failed);
  run_your_suite_tests(trim_suite, &number_failed);
  run_your_suite_tests(memcpy_suite, &number_failed);
  run_your_suite_tests(strlen_suite, &number_failed);
  run_your_suite_tests(strrchr_suite, &number_failed);
  run_your_suite_tests(strstr_suite, &number_failed);
  run_your_suite_tests(to_upper_suite, &number_failed);
  run_your_suite_tests(to_lower_suite, &number_failed);
  run_your_suite_tests(sscanf_suite, &number_failed);
  run_your_suite_tests(sprintf_suite, &number_failed);

  return number_failed == 0 ? 0 : 1;
}

void run_your_suite_tests(Suite* s, int* number_failed) {
  SRunner* runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  *number_failed += srunner_ntests_failed(runner);
  srunner_free(runner);
}
