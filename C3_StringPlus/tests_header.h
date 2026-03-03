#ifndef S21_TEST
#define S21_TEST

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite* create_memchr_suite();
Suite* create_memcmp_suite();
Suite* create_strchr_suite();
Suite* create_strcspn_suite();
Suite* create_strerror_suite();
Suite* create_strpbrk_suite();
Suite* create_strtok_suite();
Suite* create_strncat_suite();
Suite* create_strncmp_suite();
Suite* create_memset_suite();
Suite* create_strncpy_suite();
Suite* create_insert_suite();
Suite* create_trim_suite();
Suite* create_memcpy_suite();
Suite* create_strlen_suite();
Suite* create_strrchr_suite();
Suite* create_strstr_suite();
Suite* create_to_upper_suite();
Suite* create_to_lower_suite();
Suite* create_sscanf_suite();
Suite* create_sprintf_suite();

#endif