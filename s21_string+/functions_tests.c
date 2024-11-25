#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(strncmp_equal) {
  // Arrange
  char *str1 = "Good12345";
  char *str2 = "Good56789";
  int my_rez, orig_rez;
  // Act
  my_rez = s21_strncmp(str1, str2, 4);
  orig_rez = memcmp(str1, str2, 4);
  // Assert
  ck_assert_int_eq(my_rez, orig_rez);
}
END_TEST

START_TEST(strncmp_lower) {
  // Arrange
  char *str1 = "Good12345";
  char *str2 = "Good56789";
  int my_rez, orig_rez;
  // Act
  if (s21_strncmp(str1, str2, 5) < 0) my_rez = -1;
  if (memcmp(str1, str2, 5) < 0) orig_rez = -1;
  // Assert
  ck_assert_int_eq(my_rez, orig_rez);
}
END_TEST

START_TEST(strncmp_higher) {
  // Arrange
  char *str1 = "Good56789";
  char *str2 = "Good12345";
  int my_rez, orig_rez;
  // Act
  if (s21_strncmp(str1, str2, 5) > 0) my_rez = 1;
  if (memcmp(str1, str2, 5) > 0) orig_rez = 1;
  // Assert
  ck_assert_int_eq(my_rez, orig_rez);
}
END_TEST

START_TEST(strncat_test) {
  char str1[16] = "Good";
  char str2[10] = "123456789";
  s21_strncat(str1, str2, 3);

  char original_str1[16] = "Good";
  char original_str2[10] = "123456789";
  strncat(original_str1, original_str2, 3);

  ck_assert_str_eq(str1, original_str1);
}
END_TEST

START_TEST(memset_test) {
  // Arrange
  char rez[10] = "123456789";
  s21_memset(rez, '0', 5);

  char original_rez[10] = "123456789";
  memset(original_rez, '0', 5);

  ck_assert_str_eq(rez, (char *)original_rez);
}
END_TEST

START_TEST(strncpy_test) {
  // Arrange
  char rez[10] = "123456789";
  char buff[16] = "qwertyqwerty";
  s21_strncpy(rez, buff, 5);

  char original_rez[10] = "123456789";
  char original_buff[16] = "qwertyqwerty";
  strncpy(original_rez, original_buff, 5);

  ck_assert_str_eq(rez, (char *)original_rez);
}
END_TEST

START_TEST(strpbrk_test) {
  // Arrange
  char str[10] = "123456789w";
  char buff[16] = "qwertyqwerty";
  char *rez = s21_strpbrk(rez, buff);

  char original_str[10] = "123456789w";
  char original_buff[16] = "qwertyqwerty";
  char *original_rez = strpbrk(original_rez, original_buff);

  ck_assert_pstr_eq(rez, original_rez);
}
END_TEST

START_TEST(strpbrk_empty_test) {
  // Arrange
  char str[10] = "123456789w";
  char buff[16] = "";
  char *rez = s21_strpbrk(rez, buff);

  char original_str[10] = "123456789w";
  char original_buff[16] = "";
  char *original_rez = strpbrk(original_rez, original_buff);

  ck_assert_pstr_eq(rez, original_rez);
}
END_TEST

START_TEST(strcspn_test) {
  // Arrange
  char str[11] = "123456789w";
  str[11] = '\0';
  char buff[16] = "w";
  int rez = s21_strcspn(str, buff);

  char original_str[10] = "123456789w";
  char original_buff[16] = "w";
  int original_rez = strcspn(original_str, original_buff);

  ck_assert_int_eq(rez, original_rez);
}
END_TEST

START_TEST(strcspn_2_test) {
  // Arrange
  char str[4] = "1234";
  char buff[6] = "qwerty";
  int rez = s21_strcspn(str, buff);

  char original_str[4] = "1234";
  char original_buff[6] = "qwerty";
  int original_rez = strcspn(original_str, original_buff);

  ck_assert_int_eq(rez, original_rez);
}
END_TEST

START_TEST(strcspn_empty_test) {
  // Arrange
  char str[10] = "123456789w";
  char buff[1] = "q";
  int rez = s21_strcspn(str, buff);

  char original_str[10] = "123456789w";
  char original_buff[1] = "q";
  int original_rez = strcspn(original_str, original_buff);

  ck_assert_int_eq(rez, original_rez);
}
END_TEST

START_TEST(strlen_test) {
  // Arrange
  char str[10] = "123456789w";
  int rez = s21_strlen(str);
  int original_rez = strlen(str);

  ck_assert_int_eq(rez, original_rez);
}
END_TEST

START_TEST(strlen_empty_test) {
  // Arrange
  char *str;
  int rez = s21_strlen(str);
  int original_rez = strlen(str);

  ck_assert_int_eq(rez, original_rez);
}
END_TEST

START_TEST(my_strchr_test) {
  // Arrange
  char str[10] = "123456789w";
  char *rez = s21_strchr(str, '5');
  char *original_rez = strchr(str, '5');

  ck_assert_pstr_eq(rez, original_rez);
}
END_TEST

START_TEST(my_strchr_null_test) {
  // Arrange
  char str[10] = "123456789w";
  char *rez = s21_strchr(str, '0');
  char *original_rez = strchr(str, '0');

  ck_assert_pstr_eq(rez, original_rez);
}
END_TEST

START_TEST(strstr_test) {
  // Arrange
  char str[10] = "123456789w";
  char *rez = s21_strstr(str, "23456");
  char *original_rez = strstr(str, "23456");

  ck_assert_pstr_eq(rez, original_rez);
}
END_TEST

START_TEST(strstr_null_test) {
  // Arrange
  char str[10] = "123456789w";
  char *rez = s21_strstr(str, "qwerty");
  char *original_rez = strstr(str, "qwerty");

  ck_assert_pstr_eq(rez, original_rez);
}
END_TEST

START_TEST(strstr_null_test_2) {
  // Arrange
  char *str;
  char *rez = s21_strstr(str, "qwerty");
  char *original_rez = strstr(str, "qwerty");

  ck_assert_pstr_eq(rez, original_rez);
}
END_TEST

START_TEST(memcmp_good) {
  // Arrange
  char *str1 = "Good";
  char *str2 = "Good";
  int my_rez, orig_rez;
  // Act
  my_rez = s21_memcmp(str1, str2, strlen(str1));
  orig_rez = memcmp(str1, str2, strlen(str1));
  // Assert
  ck_assert_int_eq(my_rez, orig_rez);
}
END_TEST

START_TEST(memcmp_bad) {
  // Arrange
  char *str1 = "Good";
  char *str2 = "Goad";
  int my_rez, orig_rez;
  // Act
  my_rez = s21_memcmp(str1, str2, strlen(str1));
  orig_rez = memcmp(str1, str2, strlen(str1));
  // Assert
  ck_assert_int_eq(my_rez, orig_rez);
}
END_TEST

START_TEST(memcpy_hollow) {
  // Arrange
  char src[5] = "0000";
  char dest[5] = "1234";
  dest[5] = '\0';
  char *my_rez1;
  // Act
  my_rez1 = s21_memcpy(dest, src, 4);
  // Arrange
  char orig_src[5] = "0000";
  char orig_dest[5] = "7654";
  orig_dest[5] = '\0';
  char *orig_rez1;
  // Act
  orig_rez1 = memcpy(orig_dest, orig_src, 4);
  // Assert
  ck_assert_pstr_eq(my_rez1, orig_rez1);
}
END_TEST

START_TEST(memchr_find) {
  // Arrange
  char *str1 = "Good";
  int c = 'o';
  void *my_rez;
  void *orig_rez;
  // Act
  my_rez = s21_memchr(str1, c, strlen(str1));
  orig_rez = memchr(str1, c, strlen(str1));
  // Assert
  ck_assert_pstr_eq(my_rez, orig_rez);
}
END_TEST

START_TEST(memchr_miss) {
  // Arrange
  char *str1 = "Good";
  int c = 'g';
  void *my_rez;
  void *orig_rez;
  // Act
  my_rez = s21_memchr(str1, c, strlen(str1));
  orig_rez = memchr(str1, c, strlen(str1));
  // Assert
  ck_assert_pstr_eq(my_rez, orig_rez);
}
END_TEST

START_TEST(strcat_1) {
  // Arrange
  char strcat1[8] = {'1', '2', '3', '\0'};
  char strcat_orig[8] = {'1', '2', '3', '\0'};
  char strcat2[4] = {'5', '6', '7', '\0'};
  // Act
  s21_strcat(strcat1, strcat2);
  strcat(strcat_orig, strcat2);
  // Assert
  ck_assert_pstr_eq(strcat1, strcat_orig);
}
END_TEST

START_TEST(s21_strerror_test) {
  char *test1 = s21_strerror(0);
  char *test2 = strerror(0);
  char *test3 = s21_strerror(106);
  char *test4 = strerror(106);
  char *test5 = s21_strerror(2147483647);
  char *test6 = strerror(2147483647);
  char *test7 = s21_strerror(-214748364);
  char *test8 = strerror(-214748364);
  ck_assert_uint_eq((unsigned long)*test1, (unsigned long)*test2);
  ck_assert_uint_eq((unsigned long)*test3, (unsigned long)*test4);
  ck_assert_uint_eq((unsigned long)*test5, (unsigned long)*test6);
  ck_assert_uint_eq((unsigned long)*test7, (unsigned long)*test8);
}
END_TEST

START_TEST(s21_strtok_test) {
  char str_strtok1[] = "one/two/three(four)five";
  char delim1[] = "/()";

  char str_strtok2[] = "one/two/three(four)five";
  char delim2[] = "/()";
  char *my_strtok = s21_strtok(str_strtok1, delim1);
  char *origin_strtok = strtok(str_strtok2, delim2);
  while (my_strtok != s21_NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(s21_NULL, delim1);
    origin_strtok = strtok(s21_NULL, delim2);
  }
}
END_TEST

START_TEST(s21_strrchr_test) {
  char test1[] = "0163456769";
  char test2[] = ";;;;;;H%%//#HH";
  char test3[] = "     /";
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, ' '),
                    (unsigned long)strrchr(test1, ' '));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, 'H'),
                    (unsigned long)strrchr(test2, 'H'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, '$'),
                    (unsigned long)strrchr(test2, '$'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, ';'),
                    (unsigned long)strrchr(test2, ';'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, ' '),
                    (unsigned long)strrchr(test3, ' '));
  ck_assert_str_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
}
END_TEST

START_TEST(s21_trim_test) {
  const char *original = "   Hello, World!  ";
  const char *trimmed = "Hello, World!";
  char *result = s21_trim(original, " ");
  ck_assert_str_eq(result, trimmed);
  free(result);
}
END_TEST

START_TEST(s21_insert_test) {
  const char *src = "Hello, !";
  const char *str = "World";
  size_t start_index = 7;
  const char *expected = "Hello, World!";
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(s21_to_upper_test) {
  const char *src = "hello, world!";
  const char *expected = "HELLO, WORLD!";
  char *result = s21_to_upper(src);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(s21_to_lower_test) {
  const char *src = "HELLO, WORLD!";
  const char *expected = "hello, world!";
  char *result = s21_to_lower(src);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(sprintf_simple_int) {
  char str1[10];
  char str2[10];
  char *format = "lol %d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_space_int) {
  char str1[10];
  char str2[10];
  char *format = "lol % d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_int) {
  char str1[10];
  char str2[10];
  char *format = "lol %-5d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_int) {
  char str1[10];
  char str2[10];
  char *format = "lol %+5d";
  int val = -69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_2_int) {
  char str1[10];
  char str2[10];
  char *format = "lol %+5d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_dot_int) {
  char str1[10];
  char str2[10];
  char *format = "lol %.3d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_mixed_1_int) {
  char str1[100];
  char str2[100];
  char *format = "lol %+9.3d";
  int val = 69;
  s21_sprintf(str1, format, val);
  sprintf(str2, format, val);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_mixed_2_int) {
  char str1[100];
  char str2[100];
  char *format = "%-20.5+d %-20.5+d %-20.5+d";
  for (int j = 1; j < 5; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j, j * j, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_3_int) {
  char str1[100];
  char str2[100];
  char *format = "%-20.5+d %-20.5+d %-20.5+d";
  for (int j = 1; j < 5; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, -j, -j * j, -j * j * j),
                     sprintf(str2, format, -j, -j * j, -j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_4_int) {
  char str1[100];
  char str2[100];
  char *format = "%-20+d %-20+d %-20+d";
  for (int j = 1; j < 5; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j, j * j, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_c) {
  char str1[100];
  char str2[100];
  char *format = "%c %c %c";
  for (int j = 1; j < 5; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j, j * j, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_s) {
  char str1[100];
  char str2[100];
  char *format = "%s";
  for (int j = 1; j < 5; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, "aaa"),
                     sprintf(str2, format, "aaa"));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_1_f) {
  char str1[100];
  char str2[100];
  char *format = "%20 .9f";
  for (double j = 1.0; j < 13; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j * j * j),
                     sprintf(str2, format, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_2_f) {
  char str1[100];
  char str2[100];
  char *format = "%20+f";
  for (double j = 1.0; j < 13; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j * j * j),
                     sprintf(str2, format, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_3_f) {
  char str1[100];
  char str2[100];
  char *format = "%20+f lol";
  for (double j = 1.0; j < 13; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j * j * j),
                     sprintf(str2, format, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_4_f) {
  char str1[100];
  char str2[100];
  char *format = "%20.9+f lol";
  for (double j = 1.0; j < 13; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j * j * j),
                     sprintf(str2, format, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_1_u) {
  char str1[100];
  char str2[100];
  char *format = "%-20.4u%-20.4u%-20.4ulol";
  for (unsigned int j = 10; j < 13; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j, j * j, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_2_u) {
  char str1[100];
  char str2[100];
  char *format = "%20.3u%20.3u%20.3ulol";
  for (unsigned int j = 1; j < 13; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j, j * j, j * j * j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_mixed_1_h) {
  char str1[100];
  char str2[100];
  char *format = "%hd lol";
  for (short int j = 1; j < 13; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_ld) {
  char str1[100];
  char str2[100];
  char *format = "%ldlol";
  for (long int j = 1; j < 1.3; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_ld_2) {
  char str1[100];
  char str2[100];
  char *format = "%20 ldlol";
  for (long int j = 1; j < 1.3; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_hd) {
  char str1[100];
  char str2[100];
  char *format = "%hdlol";
  for (long int j = 1; j < 1.3; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_ldazaza) {
  char str1[100];
  char str2[100];
  char *format = "%1.1ldlol";
  for (long int j = 1; j < 1.3; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_ldazaza_2) {
  char str1[100];
  char str2[100];
  char *format = "%1.1ldlol";
  for (long int j = 1; j < 1.3; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, -j, -j * j, -j * j * j),
                     sprintf(str2, format, j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

START_TEST(sprintf_hdazaza) {
  char str1[100];
  char str2[100];
  char *format = "%1.1hdlol";
  for (long int j = 1; j < 1.3; j++) {
    char str3[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, format, j, j * j, j * j * j),
                     sprintf(str2, format, j));
    ck_assert_pstr_eq(str1, str2);
  }
}
END_TEST

Suite *string_suite(void) {
  Suite *s;
  TCase *tc_strncmp_equal;
  TCase *tc_strncmp_lower;
  TCase *tc_strncmp_higher;
  TCase *tc_strncat_test;
  TCase *tc_memset_test;
  TCase *tc_strncpy_test;
  TCase *tc_strpbrk_test;
  TCase *tc_strpbrk_empty_test;
  TCase *tc_strcspn_test;
  TCase *tc_strcspn_empty_test;
  TCase *tc_strlen_test;
  TCase *tc_strlen_empty_test;
  TCase *tc_my_strchr_test;
  TCase *tc_my_strchr_null_test;
  TCase *tc_strstr_test;
  TCase *tc_strstr_null_test;
  TCase *tc_memcmp_good;
  TCase *tc_memcmp_bad;
  TCase *tc_memcpy_hollow;
  TCase *tc_memchr_find;
  TCase *tc_memchr_miss;
  TCase *tc_strcspn_2_test;
  TCase *tc_strstr_null_test_2;
  TCase *tc_strcat_1;
  TCase *tc_s21_strerror_test;
  TCase *tc_s21_strtok_test;
  TCase *tc_s21_strrchr_test;
  TCase *tc_s21_trim_test;
  TCase *tc_s21_insert_test;
  TCase *tc_s21_to_upper_test;
  TCase *tc_s21_to_lower_test;
  TCase *tc_sprintf_simple_int;
  TCase *tc_sprintf_space_int;
  TCase *tc_sprintf_plus_int;
  TCase *tc_sprintf_dot_int;
  TCase *tc_sprintf_plus_2_int;
  TCase *tc_sprintf_mixed_1_int;
  TCase *tc_sprintf_mixed_2_int;
  TCase *tc_sprintf_mixed_3_int;
  TCase *tc_sprintf_c;
  TCase *tc_sprintf_s;
  TCase *tc_sprintf_mixed_1_f;
  TCase *tc_sprintf_mixed_2_f;
  TCase *tc_sprintf_mixed_3_f;
  TCase *tc_sprintf_mixed_4_f;
  TCase *tc_sprintf_mixed_1_u;
  TCase *tc_sprintf_mixed_2_u;
  TCase *tc_sprintf_mixed_1_h;
  TCase *tc_sprintf_ld;
  TCase *tc_sprintf_hd;
  TCase *tc_sprintf_ldazaza;
  TCase *tc_sprintf_ldazaza_2;
  TCase *tc_sprintf_hdazaza;

  s = suite_create("s21_string.c");

  tc_strncmp_equal = tcase_create("strncmp_equal");
  tcase_add_test(tc_strncmp_equal, strncmp_equal);
  suite_add_tcase(s, tc_strncmp_equal);

  tc_strncmp_lower = tcase_create("strncmp_lower");
  tcase_add_test(tc_strncmp_lower, strncmp_lower);
  suite_add_tcase(s, tc_strncmp_lower);

  tc_strncmp_higher = tcase_create("strncmp_higher");
  tcase_add_test(tc_strncmp_higher, strncmp_higher);
  suite_add_tcase(s, tc_strncmp_higher);

  tc_strncat_test = tcase_create("strncat_test");
  tcase_add_test(tc_strncat_test, strncat_test);
  suite_add_tcase(s, tc_strncat_test);

  tc_memset_test = tcase_create("memset_test");
  tcase_add_test(tc_memset_test, memset_test);
  suite_add_tcase(s, tc_memset_test);

  tc_strncpy_test = tcase_create("strncpy_test");
  tcase_add_test(tc_strncpy_test, strncpy_test);
  suite_add_tcase(s, tc_strncpy_test);

  tc_strpbrk_test = tcase_create("strpbrk_test");
  tcase_add_test(tc_strpbrk_test, strpbrk_test);
  suite_add_tcase(s, tc_strpbrk_test);

  tc_strpbrk_empty_test = tcase_create("strpbrk_empty_test");
  tcase_add_test(tc_strpbrk_empty_test, strpbrk_empty_test);
  suite_add_tcase(s, tc_strpbrk_empty_test);

  tc_strcspn_test = tcase_create("strcspn_test");
  tcase_add_test(tc_strcspn_test, strcspn_test);
  suite_add_tcase(s, tc_strcspn_test);

  tc_strcspn_empty_test = tcase_create("strcspn_empty_test");
  tcase_add_test(tc_strcspn_empty_test, strcspn_empty_test);
  suite_add_tcase(s, tc_strcspn_empty_test);

  tc_strlen_test = tcase_create("strlen_test");
  tcase_add_test(tc_strlen_test, strlen_test);
  suite_add_tcase(s, tc_strlen_test);

  tc_strlen_empty_test = tcase_create("strlen_empty_test");
  tcase_add_test(tc_strlen_empty_test, strlen_empty_test);
  suite_add_tcase(s, tc_strlen_empty_test);

  tc_my_strchr_test = tcase_create("my_strchr_test");
  tcase_add_test(tc_my_strchr_test, my_strchr_test);
  suite_add_tcase(s, tc_my_strchr_test);

  tc_my_strchr_null_test = tcase_create("my_strchr_null_test");
  tcase_add_test(tc_my_strchr_null_test, my_strchr_null_test);
  suite_add_tcase(s, tc_my_strchr_null_test);

  tc_strstr_test = tcase_create("strstr_test");
  tcase_add_test(tc_strstr_test, strstr_test);
  suite_add_tcase(s, tc_strstr_test);

  tc_strstr_null_test = tcase_create("strstr_null_test");
  tcase_add_test(tc_strstr_null_test, strstr_null_test);
  suite_add_tcase(s, tc_strstr_null_test);

  tc_memcmp_good = tcase_create("memcmp_good");
  tcase_add_test(tc_memcmp_good, memcmp_good);
  suite_add_tcase(s, tc_memcmp_good);

  tc_memcmp_bad = tcase_create("memcmp_bad");
  tcase_add_test(tc_memcmp_bad, memcmp_bad);
  suite_add_tcase(s, tc_memcmp_bad);

  tc_memcpy_hollow = tcase_create("memcpy_hollow");
  tcase_add_test(tc_memcpy_hollow, memcpy_hollow);
  suite_add_tcase(s, tc_memcpy_hollow);

  tc_memchr_find = tcase_create("memchr_find");
  tcase_add_test(tc_memchr_find, memchr_find);
  suite_add_tcase(s, tc_memchr_find);

  tc_memchr_miss = tcase_create("memchr_miss");
  tcase_add_test(tc_memchr_miss, memchr_miss);
  suite_add_tcase(s, tc_memchr_miss);

  tc_strcspn_2_test = tcase_create("strcspn_2_test");
  tcase_add_test(tc_strcspn_2_test, strcspn_2_test);
  suite_add_tcase(s, tc_strcspn_2_test);

  tc_strstr_null_test_2 = tcase_create("strstr_null_test_2");
  tcase_add_test(tc_strstr_null_test_2, strstr_null_test_2);
  suite_add_tcase(s, tc_strstr_null_test_2);

  tc_strcat_1 = tcase_create("strcat_1");
  tcase_add_test(tc_strcat_1, strcat_1);
  suite_add_tcase(s, tc_strcat_1);

  tc_s21_strerror_test = tcase_create("s21_strerror_test");
  tcase_add_test(tc_s21_strerror_test, s21_strerror_test);
  suite_add_tcase(s, tc_s21_strerror_test);

  tc_s21_strtok_test = tcase_create("s21_strtok_test");
  tcase_add_test(tc_s21_strtok_test, s21_strtok_test);
  suite_add_tcase(s, tc_s21_strtok_test);

  tc_s21_strrchr_test = tcase_create("s21_strrchr_test");
  tcase_add_test(tc_s21_strrchr_test, s21_strrchr_test);
  suite_add_tcase(s, tc_s21_strrchr_test);

  tc_s21_trim_test = tcase_create("s21_trim_test");
  tcase_add_test(tc_s21_trim_test, s21_trim_test);
  suite_add_tcase(s, tc_s21_trim_test);

  tc_s21_insert_test = tcase_create("s21_insert_test");
  tcase_add_test(tc_s21_insert_test, s21_insert_test);
  suite_add_tcase(s, tc_s21_insert_test);

  tc_s21_to_upper_test = tcase_create("s21_to_upper_test");
  tcase_add_test(tc_s21_to_upper_test, s21_to_upper_test);
  suite_add_tcase(s, tc_s21_to_upper_test);

  tc_s21_to_lower_test = tcase_create("s21_to_lower_test");
  tcase_add_test(tc_s21_to_lower_test, s21_to_lower_test);
  suite_add_tcase(s, tc_s21_to_lower_test);

  tc_sprintf_simple_int = tcase_create("tc_sprintf_simple_int");
  tcase_add_test(tc_sprintf_simple_int, sprintf_simple_int);
  suite_add_tcase(s, tc_sprintf_simple_int);

  tc_sprintf_space_int = tcase_create("tc_sprintf_space_int");
  tcase_add_test(tc_sprintf_space_int, sprintf_space_int);
  suite_add_tcase(s, tc_sprintf_space_int);

  tc_sprintf_plus_int = tcase_create("tc_sprintf_plus_int");
  tcase_add_test(tc_sprintf_plus_int, sprintf_plus_int);
  suite_add_tcase(s, tc_sprintf_plus_int);

  tc_sprintf_dot_int = tcase_create("tc_sprintf_dot_int");
  tcase_add_test(tc_sprintf_dot_int, sprintf_dot_int);
  suite_add_tcase(s, tc_sprintf_dot_int);

  tc_sprintf_plus_2_int = tcase_create("tc_sprintf_plus_2_int");
  tcase_add_test(tc_sprintf_plus_2_int, sprintf_plus_2_int);
  suite_add_tcase(s, tc_sprintf_plus_2_int);

  tc_sprintf_mixed_1_int = tcase_create("tc_sprintf_mixed_1_int");
  tcase_add_test(tc_sprintf_mixed_1_int, sprintf_mixed_1_int);
  suite_add_tcase(s, tc_sprintf_mixed_1_int);

  tc_sprintf_mixed_2_int = tcase_create("tc_sprintf_mixed_2_int");
  tcase_add_test(tc_sprintf_mixed_2_int, sprintf_mixed_2_int);
  suite_add_tcase(s, tc_sprintf_mixed_2_int);

  tc_sprintf_mixed_3_int = tcase_create("tc_sprintf_mixed_3_int");
  tcase_add_test(tc_sprintf_mixed_3_int, sprintf_mixed_3_int);
  suite_add_tcase(s, tc_sprintf_mixed_3_int);

  tc_sprintf_c = tcase_create("tc_sprintf_c");
  tcase_add_test(tc_sprintf_c, sprintf_c);
  suite_add_tcase(s, tc_sprintf_c);

  tc_sprintf_s = tcase_create("tc_sprintf_s");
  tcase_add_test(tc_sprintf_s, sprintf_s);
  suite_add_tcase(s, tc_sprintf_s);

  tc_sprintf_mixed_1_f = tcase_create("tc_sprintf_mixed_1_f");
  tcase_add_test(tc_sprintf_mixed_1_f, sprintf_mixed_1_f);
  suite_add_tcase(s, tc_sprintf_mixed_1_f);

  tc_sprintf_mixed_2_f = tcase_create("tc_sprintf_mixed_2_f");
  tcase_add_test(tc_sprintf_s, sprintf_mixed_2_f);
  suite_add_tcase(s, tc_sprintf_mixed_2_f);

  tc_sprintf_mixed_3_f = tcase_create("tc_sprintf_mixed_3_f");
  tcase_add_test(tc_sprintf_s, sprintf_mixed_3_f);
  suite_add_tcase(s, tc_sprintf_mixed_3_f);

  tc_sprintf_mixed_4_f = tcase_create("tc_sprintf_mixed_4_f");
  tcase_add_test(tc_sprintf_s, sprintf_mixed_4_f);
  suite_add_tcase(s, tc_sprintf_mixed_4_f);

  tc_sprintf_mixed_1_u = tcase_create("tc_sprintf_mixed_1_u");
  tcase_add_test(tc_sprintf_mixed_1_u, sprintf_mixed_1_u);
  suite_add_tcase(s, tc_sprintf_mixed_1_u);

  tc_sprintf_mixed_2_u = tcase_create("tc_sprintf_mixed_2_u");
  tcase_add_test(tc_sprintf_mixed_1_u, sprintf_mixed_2_u);
  suite_add_tcase(s, tc_sprintf_mixed_2_u);

  tc_sprintf_mixed_1_h = tcase_create("tc_sprintf_mixed_1_h");
  tcase_add_test(tc_sprintf_mixed_1_h, sprintf_mixed_1_h);
  suite_add_tcase(s, tc_sprintf_mixed_1_h);

  tc_sprintf_ld = tcase_create("tc_sprintf_ld");
  tcase_add_test(tc_sprintf_ld, sprintf_ld);
  suite_add_tcase(s, tc_sprintf_ld);

  tc_sprintf_hd = tcase_create("tc_sprintf_hd");
  tcase_add_test(tc_sprintf_hd, sprintf_hd);
  suite_add_tcase(s, tc_sprintf_hd);

  tc_sprintf_ldazaza = tcase_create("tc_sprintf_ldazaza");
  tcase_add_test(tc_sprintf_ldazaza, sprintf_ldazaza);
  suite_add_tcase(s, tc_sprintf_ldazaza);

  tc_sprintf_ldazaza_2 = tcase_create("tc_sprintf_ldazaza_2");
  tcase_add_test(tc_sprintf_ldazaza_2, sprintf_ldazaza_2);
  suite_add_tcase(s, tc_sprintf_ldazaza_2);

  tc_sprintf_hdazaza = tcase_create("tc_sprintf_hdazaza");
  tcase_add_test(tc_sprintf_hdazaza, sprintf_hdazaza);
  suite_add_tcase(s, tc_sprintf_hdazaza);

  return s;
}

int main(void) {
  int failed = 0;
  Suite *s;
  SRunner *runner;

  s = string_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
