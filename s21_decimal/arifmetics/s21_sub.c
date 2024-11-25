#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int out = 0;
  int scale_overflow;
  unsigned long long carry = 0;

  scale_overflow = normalize_scales(&value_1, &value_2);

  int sign_val1 = get_sign(value_1);
  int sign_val2 = get_sign(value_2);

  if (sign_val1 != sign_val2) {
    value_2.bits[3] ^= SIGN;
    return s21_add(value_1, value_2, result);
  }

  unsigned int borrow = 0;
  unsigned int tmp;
  s21_decimal *minued;
  s21_decimal *subtrahend;

  if (greater_or_equal(value_1, value_2)) {
    minued = &value_2;
    subtrahend = &value_1;
    minued->bits[3] ^= SIGN;
  } else {
    minued = &value_1;
    subtrahend = &value_2;
  }

  for (int i = 0; i < 3; i++) {
    tmp = (unsigned int)minued->bits[i] - (unsigned int)subtrahend->bits[i] -
          borrow;

    borrow = (unsigned int)minued->bits[i] <
                     (unsigned int)subtrahend->bits[i] + borrow
                 ? 1
                 : 0;

    result->bits[i] = (int)tmp;
  }

  result->bits[3] = minued->bits[3];

  if (borrow != 0) {
    // Инвертируем результат и меняем знак
    for (int i = 0; i <= 2; i++) {
      result->bits[i] = ~result->bits[i];
    }

    int count = 0;

    for (int i = 0; i < 3; i++) {
      if (result->bits[i] == (int)MAXBIT) count++;
    }

    if (count == 3)
      carry = 1;
    else {
      for (int i = 0; i <= count; i++) {
        result->bits[i] += 1;
      }
    }

    result->bits[3] ^= SIGN;
  }

  if (carry != 0 || scale_overflow) {
    int sign_r = get_sign(*result);
    if (sign_r == 0) {
      out = 1;
    } else {
      out = 2;
    }
  }

  return out;
}
