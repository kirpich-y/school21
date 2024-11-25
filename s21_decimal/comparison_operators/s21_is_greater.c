#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  int sign1 = get_sign(value1);
  int sign2 = get_sign(value2);
  int result = 1;
  normalize_scales(&value1, &value2);

  // int bits[4] = {0, 0, 0, 1} Ноль это мантиса

  if (sign1 != sign2) {
    if (sign1 == 1) result = 0;
  } else if (sign1 == 0) {
    for (int i = 2; i >= 0; i--) {  // {0, 0, 0, 1} - 0
      if (value1.bits[i] > value2.bits[i]) {
        result = 1;  // если первый массив больше второго
        break;
      } else if (value1.bits[i] < value2.bits[i]) {
        result = 0;  // если второй массив больше первого
        break;
      }
      if (i == 0)  // Нужно протестить, возможно лишнее
        result = 0;
    }
  } else {
    for (int i = 2; i >= 0; i--) {
      if (value1.bits[i] < value2.bits[i]) {
        result = 1;  // если первый массив больше второго
        break;
      } else if (value1.bits[i] > value2.bits[i]) {
        result = 0;  // если второй массив больше первого
        break;
      }
      if (i == 0) result = 0;
    }
  }
  return result;
}
