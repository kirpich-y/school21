#include <stdarg.h>
#include <stdio.h>

#include "../s21_string.h"
//#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#define BUFF_SIZE BUFSIZ
#define s21_NULL ((void *)0)

struct options {
  char flag[10];
  long unsigned int left;
  long unsigned int right;
  long unsigned int accuracy;
  long unsigned int type;
  long unsigned int space;
  long unsigned int plus;
  int h;
  int l;
};

long unsigned int getlength(char *str) {
  int length = 0;
  if (str == s21_NULL) {
    length = -1;
  } else {
    for (int i = 0; str[i] != '\0'; i++) {
      length++;
    }
  }
  return length;
}

char *findchar(const char *str, int ch) {
  char target_char = (char)ch;
  while (*str != target_char && *str != '\0') {
    str++;
  }
  if (*str == target_char) {
    return (char *)str;
  }
  return s21_NULL;
}

void intToStr(int num, char *str, int *length) {
  int digit;
  int isNegative = 0;
  if (num < 0) {
    num *= -1;
    isNegative = 1;
  }
  do {
    digit = num % 10;
    num /= 10;
    *str++ = '0' + digit;
    *length += 1;
  } while (num > 0);
  if (isNegative == 1) *str++ = '-';
  *str = '\0';
}

void doubleToDigits(double number, char *str, int accuracy) {
  int integerPart = (int)(number);
  int count = 1;
  char buffer[10];
  int length = 0;
  intToStr(integerPart, buffer, &length);
  if (number < 0) {
    *str = '-';
    str++;
  }
  for (int i = length - 1; i >= 0; i--) {
    str[length - 1 - i] = buffer[i];
  }
  str[length] = '.';
  double fractionalPart = number - integerPart;
  while (count <= accuracy) {
    fractionalPart *= 10;
    str[length + count] = '0' + (int)(fractionalPart);
    count++;
    fractionalPart -= (int)(fractionalPart);
  }
  str[length + count] = '\0';
}

void convert_to_options(char *flags, struct options *opt) {
  for (long unsigned int i = 1; i < getlength(flags); i++) {
    if (flags[i] == 'h') opt->left = 1;
    if (flags[i] == 'l') opt->left = 1;
    if (flags[i] == '-') {
      int count = 0;
      i++;
      while (flags[i] >= '0' && flags[i] <= '9' && flags[i] != '\0') {
        count *= 10;
        count += flags[i] - '0';
        i++;
      }
      i -= 1;
      opt->left = count;
      continue;
    }
    if (flags[i] == '.') {
      int count = 0;
      i++;
      while (flags[i] >= '0' && flags[i] <= '9' && flags[i] != '\0') {
        count *= 10;
        count += flags[i] - '0';
        i++;
      }
      i -= 1;
      opt->accuracy = count;
      continue;
    }
    if (flags[i] >= '0' && flags[i] <= '9' && flags[i] != '\0') {
      int count = 0;
      while (flags[i] >= '0' && flags[i] <= '9' && flags[i] != '\0') {
        count *= 10;
        count += flags[i] - '0';
        i++;
      }
      i -= 1;
      opt->right = count;
      continue;
    }
    if (flags[i] == ' ') opt->space = 1;
    if (flags[i] == '+') opt->plus = 1;
  }
}

void uintToStr(unsigned int num, char *str) {
  unsigned int digit;
  int isNegative = 0;
  do {
    digit = num % 10;
    num /= 10;

    *str++ = '0' + digit;
  } while (num > 0);
  if (isNegative == 1) *str++ = '-';
  *str = '\0';
}

int get_flags(char *flags, const char *format) {
  int res = 0;
  int i;
  for (i = 0; findchar("csdfuhl", *format) == NULL; i++) {
    flags[i] = *format;
    format++;
    res++;
  }
  flags[i] = '\0';
  return res;
}

int plus_flag(char *flags, char *str, int value, int minus) {
  int res = 0;
  if ((findchar(flags, '+') != NULL) && (value >= 0)) {
    *str = '+';
    res = 1;
  }
  if ((findchar(flags, '+') != NULL) && (minus == 1)) {
    *str = '-';
    res = 1;
  }
  return res;
}

int minus_flag(char *flags, char *str, int length, int value) {
  int res = 0;
  if (findchar(flags, '-') != NULL) {
    for (int i = length; i < value; i++) {
      *str = ' ';
      str++;
      res++;
    }
  }
  return res;
}

void HintToStr(short int num, char *str, int *length) {
  short int digit;
  int isNegative = 0;
  if (num < 0) {
    num *= -1;
    isNegative = 1;
  }
  do {
    digit = num % 10;
    num /= 10;
    *str++ = '0' + digit;
    *length += 1;
  } while (num > 0);
  if (isNegative == 1) *str++ = '-';
  *str = '\0';
}

void LintToStr(long int num, char *str, int *length) {
  long int digit;
  int isNegative = 0;
  if (num < 0) {
    num *= -1;
    isNegative = 1;
  }
  do {
    digit = num % 10;
    num /= 10;
    *str++ = '0' + digit;
    *length += 1;
  } while (num > 0);
  if (isNegative == 1) *str++ = '-';
  *str = '\0';
}

int space_flag(char *str, int value, int space, int plus) {
  int res = 0;
  if (space == 1 && value >= 0 && plus == 0) {
    *str = ' ';
    res = 1;
  }
  return res;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;
  int d;
  double f;
  unsigned int u;
  //    char c;
  int d_2;
  short int hd;
  short int hd_2;
  long int ld;
  long int ld_2;
  char *s;
  char buffer[100];
  int count = 0;
  char *start_index = str;
  char flags[100];
  va_start(ap, format);
  while (*format) {
    if (*format == '%') {
      format += get_flags(flags, format);
      struct options opt;
      opt.accuracy = 0;
      opt.space = 0;
      opt.right = 0;
      opt.left = 0;
      opt.plus = 0;
      opt.h = 0;
      opt.l = 0;
      int length;
      char *start = str;
      //            char* d_start;
      int minus_counter;
      convert_to_options(flags, &opt);
      char c = *format;
      if (opt.h == 1) c = 'h';
      if (opt.l == 1) c = 'l';
      switch (c) {
        case 'c':
          c = (char)va_arg(ap, int);
          *str = c;
          break;

        case 's':
          s = va_arg(ap, char *);
          while (*s != '\0') {
            *str = *s;
            str++;
            s++;
          }
          str--;
          break;

        case 'l':
          format++;
          // printf("c is %c\n",  *format + 1);
          ld = (long int)va_arg(ap, int);
          // printf("ld is %d\n",  ld);
          // if ((*format + 1) == 'd') {
          ld_2 = ld;
          // printf("ld is %d\n",  ld);
          if (ld < 0) ld_2 = -ld;
          if (opt.accuracy == 0) opt.accuracy = 0;
          char *d_start = str;
          if (opt.plus == 1 && opt.left > 0) {
            if (ld >= 0) {
              *str = '+';
            } else {
              *str = '-';
            }
            str++;
            if (d < 0) d = -d;
          }
          LintToStr(ld, buffer, &length);
          if (space_flag(str, ld, opt.space, opt.plus) == 1) str++;
          count = getlength(buffer) - 1;
          if (opt.accuracy > 0) {
            for (long unsigned int i = 0; i < opt.accuracy - count - 1; i++) {
              *str = '0';
              str++;
            }
          }
          if (opt.right > 0 && opt.accuracy == 0) {
            int kostyl = 0;
            if (opt.space == 1 && d > 0) kostyl--;
            for (long unsigned int i = 0;
                 i < opt.right - count - 1 + kostyl + 1; i++) {
              *str = ' ';
              str++;
            }
          }
          while (count != -1) {
            *str = buffer[count];
            str++;
            count--;
          }
          length = str - start;
          minus_counter = minus_flag(flags, str, length, opt.left);
          if (minus_counter != 0) str += minus_counter;
          if (opt.right > 0 && opt.accuracy > 0) {
            str = d_start;
            length = 0;
            char buffer_2[100];
            LintToStr(ld_2, buffer_2, &length);
            int index = opt.right - opt.accuracy - 1;
            if (opt.accuracy < getlength(buffer_2))
              index = opt.right - getlength(buffer_2) - 1;
            // printf("len %d buffer %s d_2 %d d %d\n", getlength(buffer_2),
            // buffer_2, d_2, d);
            for (int i = 0; i < index; i++) {
              *str = ' ';
              str++;
            }
            if (opt.plus == 1 && ld >= 0) {
              *str = '+';
              str++;
            }
            if (ld < 0) {
              *str = '-';
              str++;
            }
            for (long unsigned int i = 0;
                 i < opt.accuracy - getlength(buffer_2) &&
                 opt.accuracy > getlength(buffer_2);
                 i++) {
              *str = '0';
              str++;
            }
            for (int i = getlength(buffer_2) - 1; i >= 0; i--) {
              *str = buffer_2[i];
              str++;
            }
          }
          str--;
          // }
          break;

        case 'd':
          d = va_arg(ap, int);
          d_2 = d;
          if (d < 0) d_2 = -d;
          if (opt.accuracy == 0) opt.accuracy = 0;
          d_start = str;
          if (opt.plus == 1 && opt.left > 0) {
            if (d >= 0) {
              *str = '+';
            } else {
              *str = '-';
            }
            str++;
            if (d < 0) d = -d;
          }
          intToStr(d, buffer, &length);
          if (space_flag(str, d, opt.space, opt.plus) == 1) str++;
          count = getlength(buffer) - 1;
          if (opt.accuracy > 0) {
            for (long unsigned int i = 0; i < opt.accuracy - count - 1; i++) {
              *str = '0';
              str++;
            }
          }
          if (opt.right > 0 && opt.accuracy == 0) {
            int kostyl = 0;
            if (opt.space == 1 && d > 0) kostyl--;
            for (long unsigned int i = 0; i < opt.right - count - 1 + kostyl;
                 i++) {
              *str = ' ';
              str++;
            }
          }
          while (count != -1) {
            *str = buffer[count];
            str++;
            count--;
          }
          length = str - start;
          minus_counter = minus_flag(flags, str, length, opt.left);
          if (minus_counter != 0) str += minus_counter;
          if (opt.right > 0 && opt.accuracy > 0) {
            str = d_start;
            length = 0;
            char buffer_2[100];
            intToStr(d_2, buffer_2, &length);
            int index = opt.right - opt.accuracy - 1;
            if (opt.accuracy < getlength(buffer_2))
              index = opt.right - getlength(buffer_2) - 1;
            // printf("len %d buffer %s d_2 %d d %d\n", getlength(buffer_2),
            // buffer_2, d_2, d);
            for (int i = 0; i < index; i++) {
              *str = ' ';
              str++;
            }
            if (opt.plus == 1 && d >= 0) {
              *str = '+';
              str++;
            }
            if (d < 0) {
              *str = '-';
              str++;
            }
            for (long unsigned int i = 0;
                 i < opt.accuracy - getlength(buffer_2) &&
                 opt.accuracy > getlength(buffer_2);
                 i++) {
              *str = '0';
              str++;
            }
            for (int i = getlength(buffer_2) - 1; i >= 0; i--) {
              *str = buffer_2[i];
              str++;
            }
          }
          str--;
          break;

        case 'f':
          f = va_arg(ap, double);
          if (opt.accuracy == 0) opt.accuracy = 6;
          int minus = 0;
          if (plus_flag(flags, str, (int)f, minus) == 1 && opt.right == 0)
            str++;
          doubleToDigits(f, buffer, opt.accuracy);
          count = getlength(buffer);
          if (space_flag(str, (int)f, opt.space, opt.plus) == 1) str++;
          if (opt.right > 0) {
            int kostyl = 0;
            if (opt.plus == 1 && f > 0) kostyl = -1;
            if (opt.space == 1 && f > 0) kostyl = -1;
            for (long unsigned int i = 0; i < opt.right - count + kostyl; i++) {
              *str = ' ';
              str++;
            }
          }
          if (plus_flag(flags, str, (int)f, minus) == 1 && opt.right > 0) str++;
          for (int i = 0; i < count; i++) {
            *str = buffer[i];
            str++;
          }
          length = str - start;
          minus_counter = minus_flag(flags, str, length, opt.left);
          if (minus_counter != 0) str += minus_counter;
          str--;
          break;

        case 'h':
          // if ((*format + 1) == 'd'){
          format++;
          hd = (short int)va_arg(ap, int);
          hd_2 = hd;
          // printf("hd is %d\n",  hd);
          if (hd < 0) hd_2 = -hd;
          if (opt.accuracy == 0) opt.accuracy = 0;
          d_start = str;
          if (opt.plus == 1 && opt.left > 0) {
            if (hd >= 0) {
              *str = '+';
            } else {
              *str = '-';
            }
            str++;
            if (hd < 0) hd = -hd;
          }
          HintToStr(hd, buffer, &length);
          hd_2 = hd;
          // printf("ld is %d\n",  ld);
          if (space_flag(str, hd, opt.space, opt.plus) == 1) str++;
          count = getlength(buffer) - 1;
          if (opt.accuracy > 0) {
            for (long unsigned int i = 0; i < opt.accuracy - count - 1; i++) {
              *str = '0';
              str++;
            }
          }
          if (opt.right > 0 && opt.accuracy == 0) {
            int kostyl = 0;
            if (opt.space == 1 && d > 0) kostyl--;
            for (long unsigned int i = 0;
                 i < opt.right - count + kostyl + count - 1 -
                         (getlength(buffer) - 2);
                 i++) {
              *str = ' ';
              str++;
            }
          }
          while (count != -1) {
            *str = buffer[count];
            str++;
            count--;
          }
          length = str - start;
          minus_counter = minus_flag(flags, str, length, opt.left);
          if (minus_counter != 0) str += minus_counter;
          if (opt.right > 0 && opt.accuracy > 0) {
            str = d_start;
            length = 0;
            char buffer_2[100];
            HintToStr(hd_2, buffer_2, &length);
            int index = opt.right - opt.accuracy - 1;
            if (opt.accuracy < getlength(buffer_2))
              index = opt.right - getlength(buffer_2) - 1;
            // printf("len %d buffer %s d_2 %d d %d\n", getlength(buffer_2),
            // buffer_2, d_2, d);
            for (int i = 0; i < index; i++) {
              *str = ' ';
              str++;
            }
            if (opt.plus == 1 && d >= 0) {
              *str = '+';
              str++;
            }
            if (d < 0) {
              *str = '-';
              str++;
            }
            for (long unsigned int i = 0;
                 i < opt.accuracy - getlength(buffer_2) &&
                 opt.accuracy > getlength(buffer_2);
                 i++) {
              *str = '0';
              str++;
            }
            for (int i = getlength(buffer_2) - 1; i >= 0; i--) {
              *str = buffer_2[i];
              str++;
            }
          }
          str--;
          //
          //            }
          break;

        case 'u':
          u = va_arg(ap, unsigned int);
          uintToStr(u, buffer);
          count = getlength(buffer) - 1;
          if (opt.right > 0) {
            int index = opt.right - count - 1;
            if (opt.accuracy > 0 && opt.accuracy > getlength(buffer))
              index = opt.right - opt.accuracy;
            for (int i = 0; i < index; i++) {
              *str = ' ';
              str++;
            }
          }
          if (opt.left > 0) {
            for (long unsigned int i = 0;
                 i < opt.accuracy - getlength(buffer) &&
                 opt.accuracy > getlength(buffer);
                 i++) {
              *str = '0';
              str++;
            }
          }
          while (count != -1) {
            *str = buffer[count];
            str++;
            count--;
          }
          if (opt.right > 0) {
            for (long unsigned int i = 0;
                 i < opt.accuracy - getlength(buffer) &&
                 opt.accuracy > getlength(buffer);
                 i++) {
              *str = '0';
              str++;
            }
          }
          if (opt.left > 0) {
            int index = opt.left - count - getlength(buffer) - 1;
            if (opt.accuracy > 0 && opt.accuracy > getlength(buffer))
              index = opt.left - opt.accuracy;
            for (int i = 0; i < index; i++) {
              *str = ' ';
              str++;
            }
          }
          str--;
          break;

        default:
          if (*format != '\0') printf("is char - %c\n", *format);
      }
    } else {
      *str = *format;
    }
    str++;
    format++;
  }
  *str = '\0';
  va_end(ap);

  return str - start_index;
}

// int main(){
//
//     char *format = "num is %+f";
//     char str1[BUFF_SIZE];
//     char str2[BUFF_SIZE];
//     format = "lol %d";
//     int val = 69;
//     int v1 = s21_sprintf(str1, format, val);
//     int v2 = sprintf(str2, format, val);
//     printf("%s, %d\n%s, %d\n", str1, v1, str2, v2);
//     printf("--------\n");
//
//
//     format = "%20 .9f%20 .9f%20 .9f";
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20+f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, j, j*j, j*j*j);
//         printf("20+f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//
//     format = "%20+f%20+f%20+f";
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20+f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, j, j*j, j*j*j);
//         printf("20+f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20+f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20+f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//
//     format = "%20.9+f%20.9+f%20.9+f";
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20.3+f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, j, j*j, j*j*j);
//         printf("20.3+f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//
//
//     format = "%20f%20f%20f";
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, j, j*j, j*j*j);
//         printf("20f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//
//     format = "%20f%20f%20f";
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//
//
//     format = "%-20.5+f%-20.5+f%-20.5+f";
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20.3+f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20.3+f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//     format = "%-20.3+f%-20.3+f%-20.3+f";
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20.3+f %s, %d\n", str3, v1);
//     }
//     for(double j = 1.0; j < 13; j++)
//     {
//         char str3[BUFF_SIZE];
//         v1 = sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20.3+f %s, %d\n", str3, v1);
//     }
//     printf("--------\n");
//
//
//
//     format = "%-20.5+d %-20.5+d %-20.5+d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20.3+d %s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20.3+d %s\n", str3);
//     }
//     printf("--------looolooooooooooooooo\n");
//
//
//     format = "%-20.3+d %-20.3+d %-20.3+d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20.3+d %s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20.3+d %s\n", str3);
//     }
//     printf("--------\n");
//
//
//     format = "%-20+d %-20+d %-20+d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     printf("--------\n");
//
//
//
//     format = "%-20+d %-20+d %-20+d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     printf("---------------------------------------------------------------\n");
//
//
//
//     format = "%20.3+d %20.3+d %20.3+d";
//     for(int j = 1; j < 20; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20.3+d %s\n", str3);
//     }
//     for(int j = 1; j < 20; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("20.3+d %s\n", str3);
//     }
//     printf("--------\n");
//
//
//
//     format = "%20.3+d %20.3+d %20.3+d";
//     for(int j = 1; j < 10; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20.3+d %s\n", str3);
//     }
//     for(int j = 1; j < 10; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20.3+d %s\n", str3);
//     }
//     printf("---------------------------------------------------------------\n");
//
//
//
//     format = "%-20+d %-20+d %-20+d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     printf("--------\n");
//
//
//
//     format = "%-20+d %-20+d %-20+d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20+d %s\n", str3);
//     }
//     printf("--------\n");
//
//
//     format = "%-20 d%-20 d%-20 d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20 d%s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20 d%s\n", str3);
//     }
//     printf("--------\n");
//
//
//     format = "%-20 d%-20 d%-20 d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20 d%s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("-20 d%s\n", str3);
//     }
//     printf("--------otricatelnoe\n");
//
//     format = "%20 d%20 d%20 d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20 d%s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("20 d%s\n", str3);
//     }
//     printf("--------\n");
//
//
//
//     format = "%20 d%20 d%20 d";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20 d%s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20 d%s\n", str3);
//     }
//     printf("--------\n");
//
//     format = "%20u%20u%20u";
//     for(unsigned int j = 1; j < 5; j++)
//     {
//         char str3[100];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20u%s\n", str3);
//     }
//     for(unsigned int j = 1; j < 5; j++)
//     {
//         char str3[100];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("20u%s\n", str3);
//     }
//     printf("--------\n");
//
//     format = "%-20u%-20u%-20u";
//     for(unsigned int j = 1; j < 9; j++)
//     {
//         char str3[100];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20u%s\n", str3);
//     }
//     for(unsigned int j = 1; j < 9; j++)
//     {
//         char str3[100];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20u%s\n", str3);
//     }
//     printf("--------\n");
//
//     format = "%-20+u%-20+u%-20+u";
//     for(unsigned int j = 1; j < 9; j++)
//     {
//         char str3[100];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20+u%s\n", str3);
//     }
//     for(unsigned int j = 1; j < 9; j++)
//     {
//         char str3[100];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20+u%s\n", str3);
//     }
//     printf("--------\n");
//
//     format = "%-20.4u%-20.4u%-20.4u";
//     for(unsigned int j = 1; j < 9; j++)
//     {
//         char str3[100];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20.4u%s\n", str3);
//     }
//     for(unsigned int j = 1; j < 9; j++)
//     {
//         char str3[100];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("-20.4u%s\n", str3);
//     }
//     printf("--------\n");
//
//     format = "%20.3u%20.3u%20.3u";
//     for(unsigned int j = 1; j < 15; j++)
//     {
//         char str3[100];
//         s21_sprintf(str3, format, j, j*j, j*j*j);
//         printf("20.4u%s\n", str3);
//     }
//     for(unsigned int j = 1; j < 15; j++)
//     {
//         char str3[100];
//         sprintf(str3, format, j, j*j, j*j*j);
//         printf("20.4u%s\n", str3);
//     }
//     printf("--------\n");
//
//     format = "%20 hd%20 hd%20 hd";
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20 hd%s\n", str3);
//     }
//     for(int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20 hd%s\n", str3);
//     }
//     printf("--------\n");
//
//     format = "%20 ld%20 ld%20 ld";
//     for(long int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         s21_sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20 ld%s\n", str3);
//     }
//     for(long int j = 1; j < 5; j++)
//     {
//         char str3[BUFF_SIZE];
//         sprintf(str3, format, -j, -j*j, -j*j*j);
//         printf("20 ld%s\n", str3);
//     }
//     printf("--------\n");
//
//     return 0;
// }
