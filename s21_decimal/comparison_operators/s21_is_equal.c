#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  // 0 - это плюс 1 - это минус
  int sign1 = get_sign(value1);
  int sign2 = get_sign(value2);
  int result = 1;
  normalize_scales(&value1, &value2);
  if (sign1 != sign2) {
    result = 0;
  } else {
    for (int i = 0; i < 4; i++) {
      if (value1.bits[i] != value2.bits[i]) {
        result = 0;
      }
    }
  }
  return result;
}