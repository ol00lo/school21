#include "s21_decimal.h"

int s21_decimal_to_big(s21_decimal src, s21_big_decimal* dst) {
  if (dst == NULL) return S21_DECIMAL_CONVERT_ERROR;

  memset(dst, 0, sizeof(s21_big_decimal));

  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[4] = 0;
  dst->bits[3] = 0;
  dst->bits[5] = 0;

  dst->scale = s21_get_scale(src);
  dst->sign = s21_get_sign(src);

  return S21_DECIMAL_OK;
}

int s21_big_to_decimal(s21_big_decimal src, s21_decimal* dst) {
  if (dst == NULL) return S21_DECIMAL_CONVERT_ERROR;

  s21_init_decimal(dst);
  int code = S21_DECIMAL_OK;

  s21_bank_round(&src);

  for (int i = 3; i < 6; i++) {
    if (src.bits[i] != 0) {
      code = src.sign ? S21_DECIMAL_UNDERFLOW : S21_DECIMAL_OVERFLOW;
    }
  }
  if (code == S21_DECIMAL_OK) {
    dst->bits[0] = src.bits[0];
    dst->bits[1] = src.bits[1];
    dst->bits[2] = src.bits[2];

    s21_set_scale(dst, src.scale);
    s21_set_sign(dst, src.sign);
  }

  return code;
}

int s21_big_is_zero(s21_big_decimal big_dec) {
  int result = 1;
  for (int i = 0; i < 6; i++) {
    if (big_dec.bits[i] != 0) result = 0;
  }
  return result;
}

int s21_big_compare_mantissa(s21_big_decimal d1, s21_big_decimal d2) {
  int result = 0;
  for (int i = 5; i >= 0 && result == 0; i--) {
    if (d1.bits[i] != d2.bits[i]) {
      result = (unsigned int)d1.bits[i] > (unsigned int)d2.bits[i] ? 1 : -1;
    }
  }
  return result;
}

int s21_big_mul_by_10(s21_big_decimal* big_dec) {
  unsigned long long carry = 0;

  for (int i = 0; i < 6; i++) {
    unsigned long long temp =
        ((unsigned long long)(unsigned int)big_dec->bits[i]) * 10 + carry;
    big_dec->bits[i] = (int)(temp & 0xFFFFFFFF);
    carry = temp >> 32;
  }

  return carry > 0;
}

int s21_big_normalize(s21_big_decimal* num1, s21_big_decimal* num2) {
  if (num1->scale == num2->scale) return 0;

  s21_big_decimal temp1 = *num1;
  s21_big_decimal temp2 = *num2;

  if (num1->scale < num2->scale) {
    int diff = num2->scale - num1->scale;
    for (int i = 0; i < diff; i++) {
      s21_big_mul_by_10(&temp1);
    }
    temp1.scale = num2->scale;
    *num1 = temp1;
  } else {
    int diff = num1->scale - num2->scale;
    for (int i = 0; i < diff; i++) {
      s21_big_mul_by_10(&temp2);
    }
    temp2.scale = num1->scale;
    *num2 = temp2;
  }
  return 0;
}

void s21_big_add_mantissa(s21_big_decimal a, s21_big_decimal b,
                          s21_big_decimal* result) {
  unsigned int carry = 0;
  for (int i = 0; i < S21_BIG_DECIMAL_BITS_SIZE; i++) {
    unsigned long long temp = (unsigned long long)(unsigned int)a.bits[i] +
                              (unsigned long long)(unsigned int)b.bits[i] +
                              carry;
    result->bits[i] = (int)temp;
    carry = temp >> 32;
  }
}

void s21_big_sub_mantissa(s21_big_decimal a, s21_big_decimal b,
                          s21_big_decimal* result) {
  unsigned int borrow = 0;

  for (int i = 0; i < S21_BIG_DECIMAL_BITS_SIZE; i++) {
    unsigned long long a_long = (unsigned long long)a.bits[i] & 0xFFFFFFFF;
    unsigned long long b_long = (unsigned long long)b.bits[i] & 0xFFFFFFFF;
    long long temp = a_long - b_long - borrow;

    if (b_long + borrow > a_long) {
      borrow = 1;
    } else {
      borrow = 0;
    }
    result->bits[i] = (int)temp;
  }
}

void s21_big_mul_mantissa(s21_big_decimal v1, s21_big_decimal v2,
                          s21_big_decimal* result) {
  for (int i = 0; i < S21_BIG_DECIMAL_BITS_SIZE; i++) {
    result->bits[i] = 0;
  }

  for (int i = 0; i < 3; i++) {
    if (v1.bits[i] == 0) continue;

    unsigned long long carry = 0;
    for (int j = 0; j < 3; j++) {
      unsigned long long temp =
          (unsigned long long)(unsigned int)result->bits[i + j] +
          (unsigned long long)(unsigned int)v1.bits[i] *
              (unsigned long long)(unsigned int)v2.bits[j] +
          carry;
      result->bits[i + j] = (unsigned int)(temp & 0xFFFFFFFF);
      carry = temp >> 32;
    }
    if (carry) result->bits[i + 3] = (unsigned int)carry;
  }
}

void s21_big_div_mantissa(s21_big_decimal dividend, s21_big_decimal divisor,
                          s21_big_decimal* result, s21_big_decimal* remainder) {
  for (int i = 0; i < S21_BIG_DECIMAL_BITS_SIZE; i++) {
    result->bits[i] = 0;
    remainder->bits[i] = 0;
  }

  for (int bit = 191; bit >= 0; bit--) {
    int carry = 0;
    for (int i = 0; i < S21_BIG_DECIMAL_BITS_SIZE; i++) {
      int new_carry = (remainder->bits[i] & 0x80000000) ? 1 : 0;
      remainder->bits[i] = (remainder->bits[i] << 1) | carry;
      carry = new_carry;
    }
    if (dividend.bits[bit / 32] & (1U << (bit % 32))) {
      remainder->bits[0] |= 1U;
    }
    if (s21_big_compare_mantissa(*remainder, divisor) >= 0) {
      s21_big_sub_mantissa(*remainder, divisor, remainder);

      int word_index = bit / 32;
      int bit_index = bit % 32;
      result->bits[word_index] |= (1U << bit_index);
    }
  }
}

s21_big_decimal s21_big_div_by_10(s21_big_decimal a, int* reminder) {
  unsigned long long temp = 0;
  s21_big_decimal res = {0};

  for (int i = S21_BIG_DECIMAL_BITS_SIZE - 1; i >= 0; i--) {
    temp = (temp << 32) | (unsigned long long)(unsigned int)a.bits[i];
    res.bits[i] = (unsigned int)(temp / 10);
    temp = (temp % 10);
  }
  if (reminder) {
    *reminder = (int)(temp);
  }
  return res;
}

void s21_init_decimal(s21_decimal* decimal) {
  if (decimal) {
    for (int i = 0; i < 4; i++) {
      decimal->bits[i] = 0;
    }
  }
}

int s21_get_sign(s21_decimal decimal) {
  return ((unsigned int)decimal.bits[3] >> 31) & 1;
}

void s21_set_sign(s21_decimal* decimal, int sign) {
  if (sign) {
    decimal->bits[3] |= (1U << 31);
  } else {
    decimal->bits[3] &= ~(1U << 31);
  }
}

int s21_get_scale(s21_decimal decimal) {
  return (decimal.bits[3] >> 16) & 0xFF;
}

void s21_set_scale(s21_decimal* decimal, int scale) {
  decimal->bits[3] &= ~(0xFF << 16);
  decimal->bits[3] |= (scale & 0xFF) << 16;
}

int s21_is_zero(s21_decimal decimal) {
  return (decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0);
}

void s21_copy_decimal(s21_decimal src, s21_decimal* dst) {
  if (dst) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = src.bits[i];
    }
  }
}

int s21_big_add_one(s21_big_decimal* big_decimal) {
  unsigned long long sum =
      (unsigned long long)(unsigned int)(big_decimal->bits[0] + 1);
  big_decimal->bits[0] = sum & 0xFFFFFFFF;
  unsigned int carry = (sum >> 32) & 0xFFFFFFFF;

  int i = 1;
  while (carry && i < 6) {
    sum = (unsigned long long)(unsigned int)(big_decimal->bits[i] + carry);
    big_decimal->bits[i] = sum & 0xFFFFFFFF;
    carry = (sum >> 32) & 0xFFFFFFFF;
    i++;
  }
  return carry ? S21_DECIMAL_OVERFLOW : S21_DECIMAL_OK;
}

void s21_bank_round(s21_big_decimal* src) {
  int last_rem = 0;
  int cumulative_rem = 0;
  int sign = src->sign;
  int scale = src->scale;

  while ((src->bits[3] || src->bits[4] || src->bits[5] || scale > 28) &&
         scale > 0) {
    if (last_rem != 0) cumulative_rem = 1;
    *src = s21_big_div_by_10(*src, &last_rem);
    scale--;
  }

  int is_even = (src->bits[0] & 1) == 0;

  if ((last_rem > 5) || (last_rem == 5 && cumulative_rem) ||
      (last_rem == 5 && !is_even)) {
    s21_big_add_one(src);
  }
  if ((src->bits[3] || src->bits[4] || src->bits[5]) && scale > 0) {
    *src = s21_big_div_by_10(*src, &last_rem);
    scale--;
  }
  src->scale = scale;
  src->sign = sign;
}
