#include <check.h>
#include <stdlib.h>

#include "s21_decimal.h"

static s21_decimal value1[] = {
    {{40, 0, 0, 0}},                      // +40
    {{40, 0, 0, 0x00000000}},             // +40
    {{1, 1, 0, 0}},                       // +4294967297
    {{5, 2, 1, 0x00050000}},              // +184467440822994.86213
    {{85000, 85000, 85000, 0x00000000}},  // +1567973246630384107605000
    {{0x0fffffff, 0x0fffffff, 0xffffffff,
      0x80000000}},  // -79228162496970515020414713855
    {{0, 0, 0, 0}},
    {{0, 1, 1, 0}},
};

static s21_decimal value2[] = {
    {{20, 0, 0, 0}},                   // +20
    {{30, 0, 0, 0x80000000}},          // -30
    {{1, 1, 0, 0}},                    // +4294967297
    {{2, 3, 0, 0x80020000}},           // -128849018.9
    {{5000, 5000, 5000, 0x00090000}},  // +92233720390022.594565
    {{0xffffffff, 0xffffffff, 0xffffffff,
      0x80000000}},  // -79228162514264337593543950335
    {{0, 2, 0, 0x80000000}},
    {{0, 0, 0, 0}},
};

static s21_decimal result_add[] = {
    {{60, 0, 0, 0}},                  // +60
    {{10, 0, 0, 0}},                  // +10
    {{2, 2, 0, 0}},                   // +8589934594
    {{-1995, -2999, 0, 0x00050000}},  // +184467311973975.96213
    {{0, 0, 0, 0}},                   // (overflow)
    {{0, 0, 0, 0}},                   // (overflow)
    {{0, 2, 0, 0x80000000}},
    {{0, 1, 1, 0}},
};

static s21_decimal result_sub[] = {
    {{20, 0, 0, 0}},                // +20
    {{70, 0, 0, 0}},                // +70
    {{0, 0, 0, 0x80000000}},        // -0
    {{2005, 3002, 1, 0x00050000}},  // +184467569672013.76213
    {{-89939592, -89939591, -89939591,
      0x00040000}},  // +7756906991505368314436148.4664 (overflow)
    {{0xf0000000, 0xf0000000, 0, 0}},  // +17293822573129236480
    {{0, 2, 0, 0}},
    {{0, 1, 1, 0}},
};

static s21_decimal result_mul[] = {
    {{800, 0, 0, 0}},            // +800
    {{1200, 0, 0, 0x80000000}},  // -1200
    {{1, 2, 1, 0}},              // +18446744082299486209
    {{0x80000001, 0x9999999b, 0x4ccccccd,
      0x80060000}},  // -23768448769036696545191.264257
    {{0x80000001, 0x9999999b, 0x4ccccccd,
      0x00060000}},  // +23768448769036696545191.264257 (overflow)
    {{0x80000001, 0x9999999b, 0x4ccccccd,
      0x00060000}},  // +23768448769036696545191.264257 (overflow)
    {{0, 0, 0, 0x80000000}},
    {{0, 0, 0, 0}},
};

static s21_decimal result_div[] = {
    {{2, 0, 0, 0}},  //+2
    {{0x15555555, 0x52dc032c, 0x2b151328,
      0x801C0000}},  // -1.3333333333333333333333333333
    {{1, 0, 0, 0}},  // +1
    {{0xc294725b, 0xc0fb2c02, 0x2e426101,
      0x80160000}},  // -1431655.7657777777780968419931
    {{0, 0, 0, 0}},  // +0
    {{0x97727c4d, 0x1fda30e8, 0x204fce5e,
      0x001C0000}},  // 0.9999999997817212715236752461
    {{0, 0, 0, 0}},
    {{0, 0, 0, 0}},
};

int out_add[] = {0, 0, 0, 0, 1, 2, 0, 0};  // {0, 0, 0, 0, 1, 2};

int out_sub[] = {0, 0, 0, 0, 1, 0, 0, 0};
int out_mul[] = {0, 0, 0, 0, 1, 1, 0, 0};
int out_div[] = {0, 0, 0, 0, 1, 0, 0, 3};

// Arifmetics

START_TEST(s21_add_t1) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[0], value2[0], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[0].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[0].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[0].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[0].bits[3]);
  ck_assert_int_eq(mod, out_add[0]);
}
END_TEST

START_TEST(s21_add_t2) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[1], value2[1], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[1].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[1].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[1].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[1].bits[3]);
  ck_assert_int_eq(mod, out_add[1]);
}
END_TEST

START_TEST(s21_add_t3) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[2], value2[2], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[2].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[2].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[2].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[2].bits[3]);
  ck_assert_int_eq(mod, out_add[2]);
}
END_TEST

START_TEST(s21_add_t4) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[3], value2[3], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[3].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[3].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[3].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[3].bits[3]);
  ck_assert_int_eq(mod, out_add[3]);
}
END_TEST

START_TEST(s21_add_t5) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[4], value2[4], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[4].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[4].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[4].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[4].bits[3]);
  ck_assert_int_eq(mod, out_add[4]);
}
END_TEST

START_TEST(s21_add_t6) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[5], value2[5], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[5].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[5].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[5].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[5].bits[3]);
  ck_assert_int_eq(mod, out_add[5]);
}
END_TEST

START_TEST(s21_add_t7) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[6], value2[6], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[6].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[6].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[6].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[6].bits[3]);
  ck_assert_int_eq(mod, out_add[6]);
}
END_TEST

START_TEST(s21_add_t8) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_add(value1[7], value2[7], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_add[7].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_add[7].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_add[7].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_add[7].bits[3]);
  ck_assert_int_eq(mod, out_add[7]);
}
END_TEST

START_TEST(s21_sub_t1) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[0], value2[0], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[0].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[0].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[0].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[0].bits[3]);
  ck_assert_int_eq(mod, out_sub[0]);
}
END_TEST

START_TEST(s21_sub_t2) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[1], value2[1], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[1].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[1].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[1].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[1].bits[3]);
  ck_assert_int_eq(mod, out_sub[1]);
}
END_TEST

START_TEST(s21_sub_t3) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[2], value2[2], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[2].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[2].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[2].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[2].bits[3]);
  ck_assert_int_eq(mod, out_sub[2]);
}
END_TEST

START_TEST(s21_sub_t4) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[3], value2[3], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[3].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[3].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[3].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[3].bits[3]);
  ck_assert_int_eq(mod, out_sub[3]);
}
END_TEST

START_TEST(s21_sub_t5) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[4], value2[4], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[4].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[4].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[4].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[4].bits[3]);
  ck_assert_int_eq(mod, out_sub[4]);
}
END_TEST

START_TEST(s21_sub_t6) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[5], value2[5], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[5].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[5].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[5].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[5].bits[3]);
  ck_assert_int_eq(mod, out_sub[5]);
}
END_TEST

START_TEST(s21_sub_t7) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[6], value2[6], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[6].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[6].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[6].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[6].bits[3]);
  ck_assert_int_eq(mod, out_sub[6]);
}
END_TEST

START_TEST(s21_sub_t8) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_sub(value1[7], value2[7], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_sub[7].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_sub[7].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_sub[7].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_sub[7].bits[3]);
  ck_assert_int_eq(mod, out_sub[7]);
}
END_TEST

START_TEST(s21_mul_t1) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_mul(value1[0], value2[0], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_mul[0].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_mul[0].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_mul[0].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_mul[0].bits[3]);
  ck_assert_int_eq(mod, out_mul[0]);
}
END_TEST

START_TEST(s21_mul_t2) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_mul(value1[1], value2[1], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_mul[1].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_mul[1].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_mul[1].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_mul[1].bits[3]);
  ck_assert_int_eq(mod, out_mul[1]);
}
END_TEST

START_TEST(s21_mul_t3) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_mul(value1[2], value2[2], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_mul[2].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_mul[2].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_mul[2].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_mul[2].bits[3]);
  ck_assert_int_eq(mod, out_mul[2]);
}
END_TEST

START_TEST(s21_mul_t4) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_mul(value1[3], value2[3], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_mul[3].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_mul[3].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_mul[3].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_mul[3].bits[3]);
  ck_assert_int_eq(mod, out_mul[3]);
}
END_TEST

START_TEST(s21_mul_t7) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_mul(value1[6], value2[6], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_mul[6].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_mul[6].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_mul[6].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_mul[6].bits[3]);
  ck_assert_int_eq(mod, out_mul[6]);
}
END_TEST

START_TEST(s21_mul_t8) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_mul(value1[7], value2[7], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_mul[7].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_mul[7].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_mul[7].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_mul[7].bits[3]);
  ck_assert_int_eq(mod, out_mul[7]);
}
END_TEST

START_TEST(s21_div_t1) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[0], value2[0], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[0].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[0].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[0].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[0].bits[3]);
  ck_assert_int_eq(mod, out_div[0]);
}
END_TEST

START_TEST(s21_div_t2) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[1], value2[1], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[1].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[1].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[1].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[1].bits[3]);
  ck_assert_int_eq(mod, out_div[1]);
}
END_TEST

START_TEST(s21_div_t3) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[2], value2[2], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[2].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[2].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[2].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[2].bits[3]);
  ck_assert_int_eq(mod, out_div[2]);
}
END_TEST

START_TEST(s21_div_t4) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[3], value2[3], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[3].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[3].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[3].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[3].bits[3]);
  ck_assert_int_eq(mod, out_div[3]);
}
END_TEST

START_TEST(s21_div_t5) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[4], value2[4], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[4].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[4].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[4].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[4].bits[3]);
  ck_assert_int_eq(mod, out_div[4]);
}
END_TEST

START_TEST(s21_div_t6) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[5], value2[5], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[5].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[5].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[5].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[5].bits[3]);
  ck_assert_int_eq(mod, out_div[5]);
}
END_TEST

START_TEST(s21_div_t7) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[6], value2[6], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[6].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[6].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[6].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[6].bits[3]);
  ck_assert_int_eq(mod, out_div[6]);
}
END_TEST

START_TEST(s21_div_t8) {
  // Arrange
  int mod;
  s21_decimal tmp;
  // Act
  mod = 0;
  mod = s21_div(value1[7], value2[7], &tmp);
  // Assert
  ck_assert_int_eq(tmp.bits[0], result_div[7].bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_div[7].bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_div[7].bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_div[7].bits[3]);
  ck_assert_int_eq(mod, out_div[7]);
}
END_TEST

// Convertors

START_TEST(from_int_to_decimal_1) {
  int number = 10;
  s21_decimal expected = {{10, 0, 0, 0}};
  s21_decimal received;
  int result = s21_from_int_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  int number = -10;
  s21_decimal expected = {{10, 0, 0, -2147483648}};
  s21_decimal received;
  int result = s21_from_int_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  float number = 10.0;
  s21_decimal expected = {{10, 0, 0, 0}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  float number = -1.2;
  s21_decimal expected = {{12, 0, 0, -2147418112}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  float number = 1.2;
  s21_decimal expected = {{12, 0, 0, 65536}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  float number = -1.234567;
  s21_decimal expected = {{1234567, 0, 0, -2147090432}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  float number = -1.234567 / 0.0;
  // s21_decimal expected = {{1234567, 0, 0, -2147090432}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  float number = 0.0;
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_7) {
  float number = -0.00000001;
  s21_decimal expected = {{0, 0, 0, -2147483648}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(1, result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(received.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  float number = 7922815779189785472389873664000000.0;
  // s21_decimal expected = {{1234567, 0, 0, -2147090432}};
  s21_decimal received;
  int result = s21_from_float_to_decimal(number, &received);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal dec = {{10, 0, 0, 0}};
  int expected = 10;
  int received;
  int result = s21_from_decimal_to_int(dec, &received);
  ck_assert_int_eq(1, result);
  ck_assert_int_eq(expected, received);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal dec = {{10, 10, 10, 0}};
  // int expected = 10;
  int received;
  int result = s21_from_decimal_to_int(dec, &received);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal dec = {{1234567, 0, 0, -2147090432}};
  int expected = -1;
  int received;
  int result = s21_from_decimal_to_int(dec, &received);
  ck_assert_int_eq(1, result);
  ck_assert_int_eq(expected, received);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal dec = {{1234567, 1234567, 1234567, -2147090432}};
  int received;
  int result = s21_from_decimal_to_int(dec, &received);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal dec = {{10, 0, 0, 0}};
  float received;
  float expected = 10.0;
  int result = s21_from_decimal_to_float(dec, &received);
  ck_assert_int_eq(1, result);
  ck_assert_float_eq(expected, received);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal dec = {{12, 0, 0, -2147418112}};
  float received;
  float expected = -1.2;
  int result = s21_from_decimal_to_float(dec, &received);
  ck_assert_int_eq(1, result);
  ck_assert_float_eq(expected, received);
}
END_TEST

// Other functions

START_TEST(s21_floor_test_1) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {40, 0, 0, 0}};
  s21_decimal result_floor = {.bits = {40, 0, 0, 0}};
  mod = s21_floor(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_floor.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_floor.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_floor.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_floor.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_floor_test_2) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {85, 0, 0, 0}};
  s21_decimal result_floor = {.bits = {85, 0, 0, 0}};
  mod = s21_floor(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_floor.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_floor.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_floor.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_floor.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_floor_test_3) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {85, 0, 0, 0x80000000}};
  s21_decimal result = {.bits = {85, 0, 0, 0x80000000}};
  mod = s21_floor(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result.bits[3]);
  ck_assert_int_eq(mod, 0);
}

START_TEST(s21_floor_test_4) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {78234, 0, 0, 0x80030000}};
  s21_decimal result = {.bits = {79, 0, 0, 0x80000000}};
  mod = s21_floor(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_negate_test_1) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {40, 0, 0, 0}};
  s21_decimal result_negete = {.bits = {40, 0, 0, 0x80000000}};
  mod = s21_negate(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_negete.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_negete.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_negete.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_negete.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_negate_test_2) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {40, 0, 5, 0}};
  s21_decimal result_negete = {.bits = {40, 0, 5, 0x80000000}};
  mod = s21_negate(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_negete.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_negete.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_negete.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_negete.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_negate_test_3) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {600, 2, 5, 0x001f0000}};
  s21_decimal result_negate = {.bits = {0, 0, 0, 0}};
  mod = s21_negate(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_negate.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_negate.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_negate.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_negate.bits[3]);
  ck_assert_int_eq(mod, 1);
}
END_TEST

START_TEST(s21_round_test_1) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {40, 0, 0, 0}};
  s21_decimal result_round = {.bits = {40, 0, 0, 0}};
  mod = s21_round(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_round.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_round.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_round.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_round.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_round_test_2) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {40, 5, 0, 0}};
  s21_decimal result_round = {.bits = {40, 5, 0, 0}};
  mod = s21_round(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_round.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_round.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_round.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_round.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_round_test_3) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {40, 0, 2, 0x001f0000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  mod = s21_round(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_round_test_4) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {0, 0, 0, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  mod = s21_round(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_round_test_5) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {5, 15, 0, 0x00050000}};
  s21_decimal result = {.bits = {644245, 0, 0, 0}};
  mod = s21_round(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_round_test_6) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {5000, 1500, 200, 0x001A0000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  mod = s21_round(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

START_TEST(s21_truncate_test_1) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {40, 0, 0, 0}};
  s21_decimal result_truncate = {.bits = {40, 0, 0, 0}};
  mod = s21_truncate(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result_truncate.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result_truncate.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result_truncate.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result_truncate.bits[3]);
  ck_assert_int_eq(mod, 0);
}

START_TEST(s21_truncate_test_2) {
  int mod = 0;
  s21_decimal tmp;
  s21_decimal value1 = {.bits = {80, 5, 1, 0x001f0000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  mod = s21_truncate(value1, &tmp);
  ck_assert_int_eq(tmp.bits[0], result.bits[0]);
  ck_assert_int_eq(tmp.bits[1], result.bits[1]);
  ck_assert_int_eq(tmp.bits[2], result.bits[2]);
  ck_assert_int_eq(tmp.bits[3], result.bits[3]);
  ck_assert_int_eq(mod, 0);
}
END_TEST

// comparison_operators
START_TEST(is_less1) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_less2) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{12, 0, 0, 0}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_less3) {
  s21_decimal dec1 = {{12, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_less4) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{12, 0, 0, -2147483648}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_less5) {
  s21_decimal dec1 = {{12, 0, 0, -2147483648}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_less6) {
  s21_decimal dec1 = {{12, 0, 0, 0x00050000}};
  s21_decimal dec2 = {{12, 0, 0, 0x00040000}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_less7) {
  s21_decimal dec1 = {{12, 0, 0, 0x00040000}};
  s21_decimal dec2 = {{12, 0, 0, 0x00050000}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_less8) {
  s21_decimal dec1 = {{12, 5, 0, 0x80050000}};
  s21_decimal dec2 = {{11, 5, 0, 0x80050000}};
  int received = s21_is_less(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greate1) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greate2) {
  s21_decimal dec1 = {{12, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greate3) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{12, 0, 0, 0}};
  int received = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greate4) {
  s21_decimal dec1 = {{12, 0, 0, -2147483648}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greate5) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{12, 0, 0, -2147483648}};
  int received = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greate6) {
  s21_decimal dec1 = {{10, 5, 0, 0x80040000}};
  s21_decimal dec2 = {{8, 5, 0, 0x80040000}};
  int received = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_equal1) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_equal2) {
  s21_decimal dec1 = {{11, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_equal3) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, -2147483648}};
  int received = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_not_equal1) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, -2147483648}};
  int received = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_not_equal2) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_not_equal3) {
  s21_decimal dec1 = {{11, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal10) {
  s21_decimal dec1 = {{11, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal11) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal12) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{11, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greater_or_equal13) {
  s21_decimal dec1 = {{10, 0, 0, 0x80000000}};
  s21_decimal dec2 = {{11, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greater_or_equal14) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{11, 0, 0, 0x80000000}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal6) {
  s21_decimal dec1 = {{11, 5, 100, 0x00040000}};
  s21_decimal dec2 = {{11, 4, 0, 0x00050000}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal7) {
  s21_decimal dec1 = {{11, 4, 0, 0x00070000}};
  s21_decimal dec2 = {{11, 5000000, 50000, 0x00050000}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greater_or_equal1) {
  s21_decimal dec1 = {{11, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal2) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal3) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{11, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greater_or_equal4) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{11, 0, 0, -2147483648}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal5) {
  s21_decimal dec1 = {{10, 0, 0, -2147483648}};
  s21_decimal dec2 = {{11, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_greater_or_equal8) {
  s21_decimal dec1 = {{10, 10, 10, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_greater_or_equal9) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{10, 10, 10, 0}};
  int received = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_less_or_equal1) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_less_or_equal2) {
  s21_decimal dec1 = {{5, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  int received = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_less_or_equal3) {
  s21_decimal dec1 = {{15, 0, 0, 0x80000000}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  int received = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_less_or_equal4) {
  s21_decimal dec1 = {{0, 5, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  int received = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

START_TEST(is_less_or_equal5) {
  s21_decimal dec1 = {{5, 0, 0, 0x00050000}};
  s21_decimal dec2 = {{5, 0, 0, 0x00040000}};
  int received = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(1, received);
}
END_TEST

START_TEST(is_less_or_equal6) {
  s21_decimal dec1 = {{5, 0, 0, 0}};
  s21_decimal dec2 = {{5, 0, 0, 0x80000000}};
  int received = s21_is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(0, received);
}
END_TEST

Suite *decimal_suite(void) {
  Suite *s;
  // Arifmetics
  TCase *s21_add1;
  TCase *s21_sub1;
  TCase *s21_mul1;
  TCase *s21_div1;
  // Convertors
  TCase *s21_from_int;
  TCase *s21_from_float;
  TCase *s21_from_dec_to_int;
  TCase *s21_from_dec_to_float;
  // Other functions
  TCase *s21_floor;
  TCase *s21_round;
  TCase *s21_truncate;
  TCase *s21_negate;
  // comparison_operators
  TCase *is_less_tc;
  TCase *is_greate_tc;
  TCase *is_equal_tc;
  TCase *is_not_equal_tc;
  TCase *is_greater_or_equal_tc;
  TCase *is_greater_or_equal_tc1;
  TCase *is_greater_or_equal_tc2;
  TCase *is_greater_or_equal_tc3;
  TCase *is_greater_or_equal_tc4;
  TCase *is_greater_or_equal_tc5;
  TCase *is_less_or_equal_tc;

  s = suite_create("s21_add_test");

  s21_add1 = tcase_create("s21_add_test");
  s21_sub1 = tcase_create("s21_sub_test");
  s21_mul1 = tcase_create("s21_mul_test");
  s21_div1 = tcase_create("s21_div_test");
  s21_from_int = tcase_create("s21_from_int");
  s21_from_float = tcase_create("s21_from_float");
  s21_from_dec_to_int = tcase_create("s21_from_decimal_to_int");
  s21_from_dec_to_float = tcase_create("s21_from_decimal_to_float");
  s21_floor = tcase_create("s21_floor");
  s21_round = tcase_create("s21_round");
  s21_truncate = tcase_create("s21_truncate");
  s21_negate = tcase_create("s21_negate");
  is_less_tc = tcase_create("is_less");
  is_greate_tc = tcase_create("is_greate");
  is_equal_tc = tcase_create("is_equal");
  is_not_equal_tc = tcase_create("is_not_equal");
  is_greater_or_equal_tc = tcase_create("is_greate_of_equal");
  is_greater_or_equal_tc1 = tcase_create("is_greate_of_equal1");
  is_greater_or_equal_tc2 = tcase_create("is_greate_of_equal2");
  is_greater_or_equal_tc3 = tcase_create("is_greate_of_equal3");
  is_greater_or_equal_tc4 = tcase_create("is_greate_of_equal4");
  is_greater_or_equal_tc5 = tcase_create("is_greate_of_equal5");
  is_less_or_equal_tc = tcase_create("is_less_or_equal");

  tcase_add_test(s21_add1, s21_add_t1);
  tcase_add_test(s21_add1, s21_add_t2);
  tcase_add_test(s21_add1, s21_add_t3);
  tcase_add_test(s21_add1, s21_add_t4);
  tcase_add_test(s21_add1, s21_add_t5);
  tcase_add_test(s21_add1, s21_add_t6);
  tcase_add_test(s21_add1, s21_add_t7);
  tcase_add_test(s21_add1, s21_add_t8);

  tcase_add_test(s21_sub1, s21_sub_t1);
  tcase_add_test(s21_sub1, s21_sub_t2);
  tcase_add_test(s21_sub1, s21_sub_t3);
  tcase_add_test(s21_sub1, s21_sub_t4);
  tcase_add_test(s21_sub1, s21_sub_t5);
  tcase_add_test(s21_sub1, s21_sub_t6);
  tcase_add_test(s21_sub1, s21_sub_t7);
  tcase_add_test(s21_sub1, s21_sub_t8);

  tcase_add_test(s21_mul1, s21_mul_t1);
  tcase_add_test(s21_mul1, s21_mul_t2);
  tcase_add_test(s21_mul1, s21_mul_t3);
  tcase_add_test(s21_mul1, s21_mul_t4);
  tcase_add_test(s21_mul1, s21_mul_t7);
  tcase_add_test(s21_mul1, s21_mul_t8);

  tcase_add_test(s21_div1, s21_div_t1);
  tcase_add_test(s21_div1, s21_div_t2);
  tcase_add_test(s21_div1, s21_div_t3);
  tcase_add_test(s21_div1, s21_div_t4);
  tcase_add_test(s21_div1, s21_div_t5);
  tcase_add_test(s21_div1, s21_div_t6);
  tcase_add_test(s21_div1, s21_div_t7);
  tcase_add_test(s21_div1, s21_div_t8);

  tcase_add_test(s21_from_int, from_int_to_decimal_1);
  tcase_add_test(s21_from_int, from_int_to_decimal_2);

  tcase_add_test(s21_from_float, from_float_to_decimal_1);
  tcase_add_test(s21_from_float, from_float_to_decimal_2);
  tcase_add_test(s21_from_float, from_float_to_decimal_3);
  tcase_add_test(s21_from_float, from_float_to_decimal_4);
  tcase_add_test(s21_from_float, from_float_to_decimal_5);
  tcase_add_test(s21_from_float, from_float_to_decimal_6);
  tcase_add_test(s21_from_float, from_float_to_decimal_7);
  tcase_add_test(s21_from_float, from_float_to_decimal_8);

  tcase_add_test(s21_from_dec_to_int, from_decimal_to_int_1);
  tcase_add_test(s21_from_dec_to_int, from_decimal_to_int_2);
  tcase_add_test(s21_from_dec_to_int, from_decimal_to_int_3);
  tcase_add_test(s21_from_dec_to_int, from_decimal_to_int_4);

  tcase_add_test(s21_from_dec_to_float, from_decimal_to_float_1);
  tcase_add_test(s21_from_dec_to_float, from_decimal_to_float_2);

  tcase_add_test(s21_floor, s21_floor_test_1);
  tcase_add_test(s21_floor, s21_floor_test_2);
  tcase_add_test(s21_floor, s21_floor_test_3);
  tcase_add_test(s21_floor, s21_floor_test_4);

  tcase_add_test(s21_round, s21_round_test_1);
  tcase_add_test(s21_round, s21_round_test_2);
  tcase_add_test(s21_round, s21_round_test_3);
  tcase_add_test(s21_round, s21_round_test_4);
  tcase_add_test(s21_round, s21_round_test_5);
  tcase_add_test(s21_round, s21_round_test_6);

  tcase_add_test(s21_truncate, s21_truncate_test_1);
  tcase_add_test(s21_truncate, s21_truncate_test_2);

  tcase_add_test(s21_negate, s21_negate_test_1);
  tcase_add_test(s21_negate, s21_negate_test_2);
  tcase_add_test(s21_negate, s21_negate_test_3);

  tcase_add_test(is_less_tc, is_less1);
  tcase_add_test(is_less_tc, is_less2);
  tcase_add_test(is_less_tc, is_less3);
  tcase_add_test(is_less_tc, is_less4);
  tcase_add_test(is_less_tc, is_less5);
  tcase_add_test(is_less_tc, is_less6);
  tcase_add_test(is_less_tc, is_less7);
  tcase_add_test(is_less_tc, is_less8);

  tcase_add_test(is_greate_tc, is_greate1);
  tcase_add_test(is_greate_tc, is_greate2);
  tcase_add_test(is_greate_tc, is_greate3);
  tcase_add_test(is_greate_tc, is_greate4);
  tcase_add_test(is_greate_tc, is_greate5);
  tcase_add_test(is_greate_tc, is_greate6);

  tcase_add_test(is_equal_tc, is_equal1);
  tcase_add_test(is_equal_tc, is_equal2);
  tcase_add_test(is_equal_tc, is_equal3);

  tcase_add_test(is_not_equal_tc, is_not_equal1);
  tcase_add_test(is_not_equal_tc, is_not_equal2);
  tcase_add_test(is_not_equal_tc, is_not_equal3);

  tcase_add_test(is_greater_or_equal_tc1, is_greater_or_equal1);
  tcase_add_test(is_greater_or_equal_tc2, is_greater_or_equal2);
  tcase_add_test(is_greater_or_equal_tc3, is_greater_or_equal3);
  tcase_add_test(is_greater_or_equal_tc4, is_greater_or_equal4);
  tcase_add_test(is_greater_or_equal_tc5, is_greater_or_equal5);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal6);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal7);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal8);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal9);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal10);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal11);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal12);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal13);
  tcase_add_test(is_greater_or_equal_tc, is_greater_or_equal14);

  tcase_add_test(is_less_or_equal_tc, is_less_or_equal1);
  tcase_add_test(is_less_or_equal_tc, is_less_or_equal2);
  tcase_add_test(is_less_or_equal_tc, is_less_or_equal3);
  tcase_add_test(is_less_or_equal_tc, is_less_or_equal4);
  tcase_add_test(is_less_or_equal_tc, is_less_or_equal5);
  tcase_add_test(is_less_or_equal_tc, is_less_or_equal6);

  suite_add_tcase(s, s21_add1);
  suite_add_tcase(s, s21_sub1);
  suite_add_tcase(s, s21_mul1);
  suite_add_tcase(s, s21_div1);
  suite_add_tcase(s, s21_from_int);
  suite_add_tcase(s, s21_from_float);
  suite_add_tcase(s, s21_from_dec_to_int);
  suite_add_tcase(s, s21_from_dec_to_float);
  suite_add_tcase(s, s21_floor);
  suite_add_tcase(s, s21_round);
  suite_add_tcase(s, s21_truncate);
  suite_add_tcase(s, s21_negate);
  suite_add_tcase(s, is_less_tc);
  suite_add_tcase(s, is_greate_tc);
  suite_add_tcase(s, is_equal_tc);
  suite_add_tcase(s, is_not_equal_tc);
  suite_add_tcase(s, is_greater_or_equal_tc);
  suite_add_tcase(s, is_greater_or_equal_tc1);
  suite_add_tcase(s, is_greater_or_equal_tc2);
  suite_add_tcase(s, is_greater_or_equal_tc3);
  suite_add_tcase(s, is_greater_or_equal_tc4);
  suite_add_tcase(s, is_greater_or_equal_tc5);
  suite_add_tcase(s, is_less_or_equal_tc);

  return s;
}

int main(void) {
  int failed = 0;
  Suite *s;
  SRunner *runner;

  s = decimal_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
