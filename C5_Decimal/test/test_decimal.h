#ifndef TEST_DECIMAL_H
#define TEST_DECIMAL_H

#include <check.h>

#include "../s21_decimal.h"

// Arithmetic operations
Suite* s21_add_suite(void);
Suite* s21_sub_suite(void);
Suite* s21_mul_suite(void);
Suite* s21_div_suite(void);

Suite* create_comparison_suite(void);

Suite* int_conversion_suite(void);
Suite* float_conversion_suite(void);
Suite* decimal_to_int_suite(void);
Suite* decimal_to_float_suite(void);

Suite* create_other_suite(void);

#endif