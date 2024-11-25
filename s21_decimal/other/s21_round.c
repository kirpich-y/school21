#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal subres;
  init(&subres);

  int sign = get_sign(value);

  int res = 0;
  res = s21_truncate(value, result);

  s21_sub(value, *result, &subres);

  s21_decimal remainder_plus = {.bits = {5, 0, 0, 0x00010000}};
  s21_decimal remainder_minus = {.bits = {5, 0, 0, 0x80010000}};

  int out = 0;

  if (sign == 1) {
    out = s21_is_less_or_equal(subres, remainder_minus);
  } else if (sign == 0) {
    out = s21_is_greater_or_equal(subres, remainder_plus);
  }
  if (out == 1) add_one(result);

  return res;
}
