#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int out = 0;
  int scale_overflow;
  // Приравниваем скейлы
  scale_overflow = normalize_scales(&value_1, &value_2);

  int sign_a = get_sign(value_1);
  int sign_b = get_sign(value_2);

  if (sign_a == sign_b) {
    unsigned long long carry = 0;
    for (int i = 0; i <= 2; i++) {
      unsigned long long temp =
          (unsigned long long)value_1.bits[i] + value_2.bits[i] + carry;
      result->bits[i] = (int)(temp & MAXBIT);
      carry = (temp >> 32) & MAXBIT;
    }

    result->bits[3] = value_1.bits[3];

    // overflow
    if (carry != 0 || scale_overflow) {
      if (sign_a == 0) {
        out = 1;
      } else {
        out = 2;
      }
    }
  } else {
    s21_decimal minuend, subtrahend;
    int comparison = compare_abs(value_1, value_2);

    if (comparison == 0) {
      for (int i = 0; i <= 2; i++) {
        result->bits[i] = 0;
      }
      result->bits[3] = 0;
    } else {
      if (comparison > 0) {
        compare_mod(&value_1, &minuend);
        compare_mod(&value_2, &subtrahend);
      } else {
        compare_mod(&value_2, &minuend);
        compare_mod(&value_1, &subtrahend);
      }

      s21_sub(minuend, subtrahend, result);

      if (comparison > 0) {
        result->bits[3] = value_1.bits[3];
      } else {
        result->bits[3] = value_2.bits[3];
      }
    }
  }

  if (out) {
    init(result);
  } else {
    result->bits[3] &= MASK;
  }

  return out;
}
