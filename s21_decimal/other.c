#include "s21_decimal.h"

int get_scale(s21_decimal src) { return (src.bits[3] & SC) >> 16; }

void set_scale(s21_decimal *src, int scale) {
  src->bits[3] &= ~SC;
  src->bits[3] |= (scale << 16) & SC;
}

void clone(s21_decimal src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
}

int check_decimal_fraction(s21_decimal decimal) {
  int scale = get_scale(decimal);
  if (scale == 0) return 1;

  unsigned long long low = ((unsigned long long)decimal.bits[1] << 32) |
                           (unsigned long long)decimal.bits[0];
  unsigned long long high = (unsigned long long)decimal.bits[2];
  unsigned long long pow10 = 1;

  for (int i = 0; i < scale; i++) {
    pow10 *= 10;
  }

  unsigned long long fraction_low = low % pow10;
  unsigned long long fraction_high = high % pow10;

  return fraction_low == 0 && fraction_high == 0;
}

void add_one(s21_decimal *src) {
  if (src->bits[0] != (int)MAXBIT)
    src->bits[0] += 1;
  else if (src->bits[1] != (int)MAXBIT) {
    src->bits[0] += 1;
    src->bits[1] += 1;
  } else {
    for (int i = 0; i < 3; i++) {
      src->bits[i] += 1;
    }
  }
}

int get_sign(s21_decimal src) { return (src.bits[3] & SIGN) >> 31; }

void set_sign(s21_decimal *src, int sign) {
  src->bits[3] &= ~SIGN;
  src->bits[3] |= (sign << 31) & SIGN;
}

int normalize_scales(s21_decimal *a, s21_decimal *b) {
  int overflow = 0;
  int scale_a = get_scale(*a);
  int scale_b = get_scale(*b);

  while (scale_a < scale_b) {
    if (!multiply_by_10(a)) {
      overflow = 1;
      break;  // If overflow, stop
    }
    scale_a++;
  }
  while (scale_b < scale_a) {
    if (!multiply_by_10(b)) {
      overflow = 1;
      break;  // If overflow, stop
    }
    scale_b++;
  }

  if (scale_a < 0 || scale_a > 28) overflow = 1;
  if (scale_b < 0 || scale_b > 28) overflow = 1;

  set_scale(a, scale_a);
  set_scale(b, scale_b);

  return overflow;
}

int multiply_by_10(s21_decimal *src) {
  unsigned long long temp;
  unsigned long long carry = 0;
  for (int i = 0; i <= 2; i++) {
    temp = (unsigned long long)src->bits[i] * 10 + carry;
    src->bits[i] = (int)(temp & MAXBIT);
    carry = (temp >> 32) & MAXBIT;
  }
  return carry == 0;
}

int compare_abs(s21_decimal a, s21_decimal b) {
  for (int i = 2; i >= 0; i--) {
    if (a.bits[i] > b.bits[i]) return 1;
    if (a.bits[i] < b.bits[i]) return -1;
  }
  return 0;
}

void compare_mod(s21_decimal *src, s21_decimal *dst) {
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src->bits[i];
  }
  dst->bits[3] = 0;
}

void init(s21_decimal *result) {
  for (int i = 0; i <= 4; i++) {
    result->bits[i] = 0;
  }
}

int is_zero(s21_decimal src) {
  int result = 0;
  for (int i = 0; i < 3; i++) {
    if (src.bits[i] == 0) result++;
  }
  if (result >= 3) {
    result = 1;
  } else
    result = 0;
  return result;
}

int greater_or_equal(s21_decimal a, s21_decimal b) {
  for (int i = 3; i >= 0; i--) {
    if (a.bits[i] > b.bits[i]) return 1;
    if (a.bits[i] < b.bits[i]) return 0;
  }
  return 1;
}

void init_big(big_decimal *src) {
  for (int i = 0; i < 7; i++) {
    src->bits[i] = 0;
  }
  src->scale = 0;
}

int is_zero_big(big_decimal src) {
  int result = 1;
  for (int i = 0; i < 6; ++i) {
    if (src.bits[i] != 0) {
      result = 0;
      break;
    }
  }
  return result;
}

int is_greater_big(big_decimal value_1, big_decimal value_2) {
  if (is_zero_big(value_1) && is_zero_big(value_2)) return 0;
  int result = 0;
  for (unsigned int i = 1, size = (6 - 0 + 1) * UISZ; i <= size; ++i) {
    int bit_1 = get_bit_big(value_1, size - i);
    int bit_2 = get_bit_big(value_2, size - i);

    if (bit_1 != bit_2) {
      result = (bit_1 && !bit_2);
      break;
    }
  }
  return result;
}

void set_big_scale(big_decimal *src, int dst) {
  src->scale &= ~SC;
  src->scale |= (dst << 16) & SC;
}

void from_dec_to_big(s21_decimal src, big_decimal *dst) {
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src.bits[i];
  }
  set_big_scale(dst, get_scale(src));
}

int from_big_to_dec(big_decimal src, s21_decimal *dst) {
  if (normalize_big(&src) == 1) return 1;
  for (int i = 0; i <= 2; ++i) dst->bits[i] = src.bits[i];
  set_scale(dst, src.scale);
  return 0;
}

unsigned int big_div_10(big_decimal *src) {
  unsigned int remainder = 0;
  for (int i = 6; i >= 0; i--) {
    unsigned long long divid =
        ((unsigned long long)remainder << 32) + src->bits[i];
    src->bits[i] = divid / 10;
    remainder = divid % 10;
  }
  src->scale -= 1;
  return remainder;
}

int even_big(big_decimal src) {
  while (src.scale > 0) {
    big_div_10(&src);
  }
  return big_div_10(&src) % 2 == 0;
}

int get_bit(unsigned int bits, unsigned int pos) {
  unsigned int mask = 1u << pos;
  bits &= mask;
  bits >>= pos;
  return bits;
}

int get_bit_big(big_decimal src, unsigned int pos) {
  return get_bit(src.bits[pos / UISZ], pos % UISZ);
}

void set_bit(unsigned int *bits, unsigned int pos, unsigned int bit) {
  unsigned int mask = 1u << pos;

  if (bit) {
    *bits |= mask;
  } else {
    *bits &= (~mask);
  }
}

void set_bit_big(big_decimal *src, unsigned int pos, unsigned int bit) {
  set_bit(&(src->bits[pos / UISZ]), pos % UISZ, bit);
}

void simple_add_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  unsigned int a = 0b0;  // ?
  for (unsigned int i = 0; i < UISZ * 6; ++i) {
    unsigned int sum_bits =
        get_bit_big(value_1, i) + get_bit_big(value_2, i) + a;
    set_bit_big(result, i, sum_bits & 0b1);
    a = (sum_bits >> 1) & 0b1;
  }
}

big_decimal big_pow2(unsigned int exp) {
  big_decimal val;
  init_big(&val);
  set_bit_big(&val, exp, 1);
  return val;
}

void simple_mul_big2(big_decimal *src) {
  unsigned int carry = 0;
  for (int i = 0; i <= 6; i++) {
    unsigned long long multiplied =
        ((unsigned long long)src->bits[i] << 1) + carry;
    carry = multiplied >> 32;
    src->bits[i] = multiplied & MAXBIT;
  }
}

int capacity_big(big_decimal value) {
  int capacity = (6 - 0 + 1) * UISZ - 1;
  for (; capacity >= 0; --capacity) {
    if (get_bit_big(value, capacity)) break;
  }
  return capacity;
}

void simple_mul_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  for (int capacity = capacity_big(value_2); capacity >= 0; --capacity) {
    simple_mul_big2(result);
    if (get_bit_big(value_2, capacity)) {
      simple_add_big(value_1, *result, result);
    }
  }
}

void simple_sub_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  unsigned int bor = 0;
  for (unsigned int i = 0; i < UISZ * 6; ++i) {
    unsigned int bit_diff =
        get_bit_big(value_1, i) - get_bit_big(value_2, i) - bor;
    bor = 0;
    if (bit_diff > 1) {
      bit_diff += 2;
      bor = 1;
    }
    set_bit_big(result, i, bit_diff & 0b1);
  }
}

void simple_div_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  big_decimal remainder = int_big_div(value_1, value_2, result);
  while (!is_zero_big(remainder) && result->scale < 28) {
    mul_big_by_10(&remainder);
    mul_big_by_10(result);
    result->scale += 1;
    remainder = int_big_div(remainder, value_2, result);
  }
  if (!is_zero_big(remainder)) {
    for (int i = 6; i > 2; --i) {
      if (result->bits[i] != 0) return;
    }
  }
  simple_mul_big2(&remainder);
  if (is_greater_big(remainder, value_2)) {
    big_decimal first;
    init_big(&first);
    first.bits[0] = 1u;
    simple_add_big(*result, first, result);
  }
}

void mul_big_by_10(big_decimal *src) {
  unsigned int carry = 0;
  for (int i = 0; i <= 6; i++) {
    unsigned long long multip = ((unsigned long long)src->bits[i] << 1) +
                                ((unsigned long long)src->bits[i] << 3) + carry;
    carry = multip >> 32;
    src->bits[i] = multip & MAXBIT;
  }
}

big_decimal int_big_div(big_decimal value_1, big_decimal value_2,
                        big_decimal *result) {
  big_decimal last_val2;
  while (!is_zero_big(value_1)) {
    big_decimal val2 = value_2;
    unsigned int i = 0;
    for (;; ++i) {
      if (is_greater_big(val2, value_1)) break;
      last_val2 = val2;
      simple_mul_big2(&val2);
    }
    if (i == 0)
      break;
    else {
      big_decimal res = big_pow2(i - 1);
      simple_add_big(*result, res, result);
      simple_sub_big(value_1, last_val2, &value_1);
    }
  }
  return value_1;
}

int normalize_big(big_decimal *src) {
  unsigned int remainder = 0;
  int tmp = 1;
  int five = 0;
  for (int i = 6; i > 2; --i) {
    while ((src->bits[i] && src->scale > 0) || src->scale > 28) {
      remainder = big_div_10(src);
      if (five)
        tmp = 0;
      else if (tmp && remainder == 5)
        five = 1;
      else if (remainder != 0)
        tmp = 0;
    }
  }
  if ((!tmp && remainder >= 5) || (remainder == 5 && !even_big(*src))) {
    big_decimal first;
    init_big(&first);
    first.bits[0] = 1u;
    simple_add_big(*src, first, src);
  }
  int result = 0;
  if (src->scale == 0 && src->bits[3] != 0) result = 1;
  return result;
}
