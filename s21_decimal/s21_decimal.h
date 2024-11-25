#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>

#define SIGN 0x80000000    // 10000000 00000000 00000000 00000000
#define SC 0x00ff0000      // 00000000 11111111 00000000 00000000
#define MAXBIT 0xffffffff  // 11111111 11111111 11111111 11111111
#define MASK 0x80ff0000    // 10000000 11111111 00000000 00000000

#define UISZ (sizeof(unsigned int) * 8)  // Размер unsigned int в битах

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
  int scale;
} big_decimal;

// other
int get_scale(s21_decimal src);
void set_scale(s21_decimal *src, int scale);
void clone(s21_decimal src, s21_decimal *dst);
int check_decimal_fraction(s21_decimal decimal);
void add_one(s21_decimal *src);
int get_sign(s21_decimal src);
void set_sign(s21_decimal *src, int sign);
int normalize_scales(s21_decimal *a, s21_decimal *b);
int multiply_by_10(s21_decimal *src);
int compare_abs(s21_decimal a, s21_decimal b);
void compare_mod(s21_decimal *src, s21_decimal *dst);
void init(s21_decimal *result);
int is_zero(s21_decimal src);
int get_bit_dec(s21_decimal value, unsigned int pos);
int even(s21_decimal value);
int div_by_10(s21_decimal *value);
s21_decimal get_one();
unsigned int last_digit(s21_decimal value);
int bank_round(s21_decimal value);
// big_decimal
void init_big(big_decimal *src);
int is_zero_big(big_decimal src);
int is_greater_big(big_decimal value_1, big_decimal value_2);
void set_big_scale(big_decimal *src, int dst);
void from_dec_to_big(s21_decimal src, big_decimal *dst);
int from_big_to_dec(big_decimal src, s21_decimal *dst);
unsigned int big_div_10(big_decimal *src);
int even_big(big_decimal src);
int get_bit(unsigned int bits, unsigned int pos);
int get_bit_big(big_decimal src, unsigned int pos);
void set_bit(unsigned int *bits, unsigned int pos, unsigned int bit);
void set_bit_big(big_decimal *src, unsigned int pos, unsigned int bit);
void simple_add_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);
big_decimal big_pow2(unsigned int exp);
void simple_mul_big2(big_decimal *src);
void simple_sub_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);
void simple_div_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);
void mul_big_by_10(big_decimal *src);
big_decimal int_big_div(big_decimal value_1, big_decimal value_2,
                        big_decimal *result);
int normalize_big(big_decimal *src);
int capacity_big(big_decimal value);
void simple_mul_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);
int greater_or_equal(s21_decimal a, s21_decimal b);

// Сравнения
int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);

// arifmetics
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Convertors
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
// Other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
