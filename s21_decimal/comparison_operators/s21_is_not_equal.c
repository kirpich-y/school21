#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  int result = 0;
  if (s21_is_equal(value1, value2) == 1) {
    result = 0;
  } else {
    result = 1;
  }
  return result;
}