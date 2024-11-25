#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  // код ошибки (по дефолту ноль)
  int get_error = 0;
  // Масштаб не должен превышать 28
  if (get_scale(value) > 28) {
    // Инициализация result
    init(result);
    // возращает один если ОК
    return 1;
  }
  // Если не превышает 28 копирует значения в result
  *result = value;

  set_sign(result, !get_sign(value));
  // Возращает 0
  return get_error;
}