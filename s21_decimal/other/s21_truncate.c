#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  init(result);
  int out = 0;
  int scale = get_scale(value);

  clone(value, result);

  if (scale != 0) {
    result->bits[3] &= 0xff00ffff;

    while (scale > 0) {
      unsigned int remainder = 0;
      for (int i = 2; i >= 0; i--) {
        unsigned long long temp = ((unsigned long long)remainder << 32) |
                                  (unsigned int)result->bits[i];
        result->bits[i] = temp / 10;
        remainder = temp % 10;
      }
      scale--;
    }
  } else if (scale < 0 || scale > 28) {
    out = 1;
  }

  return out;
}
