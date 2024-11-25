#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int sign = get_sign(value);
  int out = s21_truncate(value, result);
  if (sign) {
    if (!check_decimal_fraction(value)) {
      add_one(result);
    }
  }
  return out;
}
