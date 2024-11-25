#include "../s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int sign1 = get_sign(value1);
  int sign2 = get_sign(value2);
  int result = 1;
  normalize_scales(&value1, &value2);

  if (sign1 != sign2) {
    if (sign1 == 0) result = 0;
  } else if (sign1 == 0) {
    for (int i = 2; i >= 0; i--) {
      if (value1.bits[i] < value2.bits[i]) {
        result = 1;  // если первый массив меньше второго
        break;
      } else if (value1.bits[i] > value2.bits[i]) {
        result = 0;  // если второй массив меньше первого
        break;
      }
      if (i == 0) result = 0;
    }
  } else {
    for (int i = 2; i >= 0; i--) {
      if (value1.bits[i] > value2.bits[i]) {
        result = 1;  // если первый массив больше второго
        break;
      } else if (value1.bits[i] < value2.bits[i]) {
        result = 0;  // если второй массив больше первого
        break;
      }
      if (i == 0) result = 0;
    }
  }
  return result;
}
