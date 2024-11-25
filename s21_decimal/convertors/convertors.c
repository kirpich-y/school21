#include "../s21_decimal.h"

#define CORRECT 0x7F00FFFF  // 01111111000000001111111111111111
#define MAXBIT 0xffffffff
#define unit_sz (unsigned int)(sizeof(unsigned int) * 8)
#define SIGN 0x80000000  // 10000000 00000000 00000000 00000000
#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

int get_fraction_length(char *src_string) {
  while (*src_string != '.') src_string++;
  src_string++;
  int fraction = 0;
  int length = 0;
  for (int i = 0; i < 7 && src_string[i] != '\0'; i++) {
    fraction *= 10;
    fraction += (src_string[i] - 48);
    length++;
  }
  int div = 0;
  if (fraction == 0) length = 0;
  while (div == 0 && fraction != 0) {
    div = fraction % 10;
    if (div == 0) {
      length--;
      fraction = fraction / 10;
    }
  }
  return length;
}

int put_zero_to_decimal(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  return 1;
}

int is_correct_decimal(s21_decimal *number) {
  int mask = number->bits[3] & CORRECT;
  int scale = get_scale(*number);
  int result = 0;
  if (mask == 0 && scale <= 28) result = 1;
  return result;
}

int is_nan(float number) {
  unsigned int num = *(unsigned int *)&number;
  int exponent = 0;
  int mantiss = 0;
  int res = 0;
  for (int i = 30; i >= 23; --i) {
    exponent += (num >> i) & 1;
  }
  for (int i = 22; i >= 0; --i) {
    if (((num >> i) & 1) == 1) {
      mantiss = 1;
      break;
    }
  }
  if (exponent == 8 && mantiss == 1)
    res = 1;  // если все знаки экспоненты == 1 и мантисса НЕ пустая то это нан
  return res;
}

unsigned long int metamorphose(float src, int fraction_length) {
  unsigned long int result;
  float fl = fabs(src) * pow(10, fraction_length);
  result = fl;
  return result;
}

int is_inf(float number) {
  unsigned int num = *(unsigned int *)&number;
  int exponent = 0;
  int mantiss = 0;
  int res = 0;
  for (int i = 30; i >= 23; --i) {
    exponent += (num >> i) & 1;
  }
  for (int i = 22; i >= 0; --i) {
    if (((num >> i) & 1) == 1) {
      mantiss = 1;
      break;
    }
  }
  if (exponent == 8 && mantiss == 0) {  // если все знаки экспоненты == 1 и
                                        // мантисса пустая то это бесконечность
    res = 1;
    if (((num >> 31) & 1) == 1) res = -1;
  }
  return res;
}

int is_negative_float(float number) {
  int res = 0;
  unsigned int num = *(unsigned int *)&number;
  if (((num >> 31) & 1) == 1) res = 1;
  return res;
}

int is_negative_int(int number) {
  int res = 0;
  unsigned int num = *(unsigned int *)&number;
  if (((num >> 31) & 1) == 1) res = 1;
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 1;
  if (src == 0.0 ||
      (fabs(src) < 0.00000001 && fabsf(src) > MIN_FLOAT_TO_CONVERT)) {
    put_zero_to_decimal(dst);
    if (is_negative_float(src) == 1) dst->bits[3] |= (1 << 31);
  } else if (is_inf(src) != 0 || is_nan(src) != 0) {
    res = 0;
  } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
    put_zero_to_decimal(dst);
    res = 0;
  } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
    res = 0;
  } else {
    put_zero_to_decimal(dst);
    if (is_negative_float(src) == 1) dst->bits[3] |= (1 << 31);
    char src_string[64];
    sprintf(src_string, "%.6f", fabsf(src));
    int fraction_length = get_fraction_length(src_string);
    for (int i = 1; i <= fraction_length; i++) {
      src *= 10;
    }
    src = fabs(src);
    long int devider = 4294967296;
    for (int i = 0; i < 3 && src != 0; i++) {
      dst->bits[i] = (int)fmod(src, devider);
      src = (src - fmod(src, devider)) / devider;
    }
    set_scale(dst, fraction_length);
  }
  return res;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 1;
  if (!dst) {
    res = 0;
  } else {
    put_zero_to_decimal(dst);
    unsigned int usrc;
    if (is_negative_int(src) > 0) {
      dst->bits[3] |= (1 << 31);
      usrc = -src;
    } else {
      usrc = src;
    }
    dst->bits[0] = usrc;
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  unsigned long int ulr = 0;
  int result = 1;
  for (int i = 2; i >= 0; i--) {
    ulr *= 4294967296;
    ulr += *(unsigned int *)&(src.bits[i]);
  }
  int scale = get_scale(src);
  for (int i = 1; i <= scale; i++) {
    ulr = ulr / 10;
  }
  if (((ulr > 2147483648) && get_sign(src) == 0) ||
      ((ulr > 2147483649) && get_sign(src) == 1) ||
      is_correct_decimal(&src) == 0) {
    result = 0;
  } else {
    if (get_sign(src) == 1)
      *dst = -(int)ulr;
    else
      *dst = (int)ulr;
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  unsigned long int ulr = 0;
  int result = 1;
  for (int i = 2; i >= 0; i--) {
    ulr *= 4294967296;
    ulr = ulr + *(unsigned int *)&(src.bits[i]);
  }
  int scale = get_scale(src);
  long double res = ulr;
  for (int i = 1; i <= scale; i++) {
    res /= 10;
  }
  if (fabsf((float)ulr) > MAX_FLOAT_TO_CONVERT ||
      fabsf((float)ulr) < MIN_FLOAT_TO_CONVERT ||
      is_correct_decimal(&src) == 0) {
    result = 0;
  } else {
    if (get_sign(src) == 1)
      *dst = -(float)res;
    else
      *dst = (float)res;
  }
  return result;
}
