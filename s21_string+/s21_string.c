#include "s21_string.h"

#define s21_NULL ((void *)0)
#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

const char *maserror[] = {"Undefined error: 0",
                          "Operation not permitted",
                          "No such file or directory",
                          "No such process",
                          "Interrupted system call",
                          "Input/output error",
                          "Device not configured",
                          "Argument list too long",
                          "Exec format error",
                          "Bad file descriptor",
                          "No child processes",
                          "Resource deadlock avoided",
                          "Cannot allocate memory",
                          "Permission denied",
                          "Bad address",
                          "Block device required",
                          "Resource busy",
                          "File exists",
                          "Cross-device link",
                          "Operation not supported by device",
                          "Not a directory",
                          "Is a directory",
                          "Invalid argument",
                          "Too many open files in system",
                          "Too many open files",
                          "Inappropriate ioctl for device",
                          "Text file busy",
                          "File too large",
                          "No space left on device",
                          "Illegal seek",
                          "Read-only file system",
                          "Too many links",
                          "Broken pipe",
                          "Numerical argument out of domain",
                          "Result too large",
                          "Resource temporarily unavailable",
                          "Operation now in progress",
                          "Operation already in progress",
                          "Socket operation on non-socket",
                          "Destination address required",
                          "Message too long",
                          "Protocol wrong type for socket",
                          "Protocol not available",
                          "Protocol not supported",
                          "Socket type not supported",
                          "Operation not supported",
                          "Protocol family not supported",
                          "Address family not supported by protocol family",
                          "Address already in use",
                          "Can't assign requested address",
                          "Network is down",
                          "Network is unreachable",
                          "Network dropped connection on reset",
                          "Software caused connection abort",
                          "Connection reset by peer",
                          "No buffer space available",
                          "Socket is already connected",
                          "Socket is not connected",
                          "Can't send after socket shutdown",
                          "Too many references: can't splice",
                          "Operation timed out",
                          "Connection refused",
                          "Too many levels of symbolic links",
                          "File name too long",
                          "Host is down",
                          "No route to host",
                          "Directory not empty",
                          "Too many processes",
                          "Too many users",
                          "Disc quota exceeded",
                          "Stale NFS file handle",
                          "Too many levels of remote in path",
                          "RPC struct is bad",
                          "RPC version wrong",
                          "RPC prog. not avail",
                          "Program version wrong",
                          "Bad procedure for program",
                          "No locks available",
                          "Function not implemented",
                          "Inappropriate file type or format",
                          "Authentication error",
                          "Need authenticator",
                          "Device power is off",
                          "Device error",
                          "Value too large to be stored in data type",
                          "Bad executable (or shared library)",
                          "Bad CPU type in executable",
                          "Shared library version mismatch",
                          "Malformed Mach-o file",
                          "Operation canceled",
                          "Identifier removed",
                          "No message of desired type",
                          "Illegal byte sequence",
                          "Attribute not found",
                          "Bad message",
                          "EMULTIHOP (Reserved)",
                          "No message available on STREAM",
                          "ENOLINK (Reserved)",
                          "No STREAM resources",
                          "Not a STREAM",
                          "Protocol error",
                          "STREAM ioctl timeout",
                          "Operation not supported on socket",
                          "Policy not found",
                          "State not recoverable",
                          "Previous owner died",
                          "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

static const char *maserror[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t counter = 1;
  while (*str1 == *str2 && *str1 != '\0' && *str1 != '\0' && counter < n) {
    str1++;
    str2++;
    counter++;
  }

  if (*str1 == *str2) {
    result = 0;
  } else {
    if (*str1 > *str2) {
      result = 1;
    } else {
      result = -1;
    }
  }
  return result;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *res = ((char *)str);
  for (s21_size_t i = 0; i < n; i++) {
    res[i] = c;
  }
  return res;
}

char *s21_strncat(char *destination, const char *append, s21_size_t n) {
  int length = s21_strlen(destination);
  destination += length;
  for (s21_size_t i = 0; i < n; i++) {
    destination[i] = append[i];
  }
  destination[n] = '\0';
  return destination - length;
}

int s21_strlen(char *str) {
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

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *s1 = str1;
  while (*s1) {
    for (const char *s2 = str2; *s2; s2++) {
      if (*s1 == *s2) {
        return s1 - str1;
      }
    }
    s1++;
  }
  return s1 - str1;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  //    for (; i < n; i++) { зачем это тут если i стало больше нуля еще в первом
  //    цикле?????
  //        dest[i] = '\0';
  //    }
  return dest;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *p1, *p2;
  for (p1 = str1; *p1 != '\0'; p1++) {
    for (p2 = str2; *p2 != '\0'; p2++) {
      if (*p1 == *p2) {
        return (char *)p1;
      }
    }
  }
  return s21_NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (needle == s21_NULL) {
    return (char *)haystack;
  }

  for (; *haystack; haystack++) {
    const char *h, *n;
    for (h = haystack, n = needle; *h && *n && (*h == *n); h++, n++)
      ;
    if (!*n) {
      return (char *)haystack;
    }
  }

  return s21_NULL;
}

char *s21_strchr(const char *str, int ch) {
  // Приводим символ к типу char для корректного сравнения
  char target_char = (char)ch;
  while (*str != target_char && *str != '\0') {
    str++;  // Переходим к следующему символу
  }
  // Если нашли символ, возвращаем его адрес
  if (*str == target_char) {
    return (char *)str;
  }
  // Если символ не найден, возвращаем s21_NULL
  return s21_NULL;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;
  while (n--) {
    *d++ = *s++;
  }
  return dest;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *pstr = str;
  for (s21_size_t i = 0; i < n; i++) {
    if (pstr[i] == c) {
      return (void *const)&pstr[i];
    }
  }
  return s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *pstr1 = str1;
  const char *pstr2 = str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (pstr1[i] != pstr2[i]) {
      return ((int)pstr1[i] - (int)pstr2[i]);
    }
  }
  return 0;
}

char *s21_strerror(int errnum) {
  char *ptr = s21_NULL;
  if (errnum >= MAX_ERRLIST || errnum <= MIN_ERRLIST) {
    static char part1[33] = ERROR;
    static char part2[33];
    s21_errnum_tostring(part2, errnum);
    s21_strcat(part1, part2);
    ptr = part1;
  } else {
    ptr = (char *)maserror[errnum];
  }
  return (char *)ptr;
}

void s21_strcat(char *str1, char *str2) {  // конкатенация
  str1 += s21_strlen(str1);
  int n = s21_strlen(str2);
  for (int i = 0; i <= n; i++) {
    str1[i] = str2[i];
  }
}

void s21_errnum_tostring(char *str, int num) {
  int i, rem, len = 0, n;
  n = num;
  while (n != 0) {
    len++;
    n /= 10;
  }
  if (num >= 0) {
    for (i = 0; i < len; i++) {
      rem = num % 10;
      num = num / 10;
      str[len - (i + 1)] = rem + '0';
    }
  } else {
    len++;
    str[0] = '-';
    for (i = 0; i < len - 1; i++) {
      rem = num % 10;
      num = num / 10;
      str[len - (i + 1)] = rem + '0';
      if (i == len - 2) {
        str[len - (i + 1)] = (-1 * rem) + '0';
      }
    }
  }
  str[len] = '\0';
}

char *s21_strrchr(const char *str, int c) {
  char k = c;
  char *res = s21_NULL;
  for (; *str != '\0'; str++) {
    if (*str == k) {
      res = (char *)str;
    }
  }
  if (res == s21_NULL) {
    res = (char *)str;
  }
  return *res == c ? (char *)res : s21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last;
  register int ch;

  if (str == 0) {
    str = last;
  }
  do {
    if ((ch = *str++) == '\0') {
      return 0;
    }
  } while (s21_strchr(delim, ch));
  --str;
  last = str + s21_strcspn(str, delim);
  if (*last != 0) {
    *last++ = 0;
  }
  return str;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == NULL || str == NULL) {
    return NULL;
  }

  // Определяем длину входных строк
  size_t src_len = 0;
  while (src[src_len] != '\0') {
    src_len++;
  }

  size_t str_len = 0;
  while (str[str_len] != '\0') {
    str_len++;
  }

  // Если start_index превышает длину исходной строки, вставляем str в конец src
  if (start_index > src_len) {
    start_index = src_len;
  }

  // Выделяем память для новой строки
  size_t new_len = src_len + str_len;
  char *result = (char *)malloc((new_len + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;  // Обработка ошибки выделения памяти
  }

  // Копируем первую часть исходной строки до start_index
  for (size_t i = 0; i < start_index; i++) {
    result[i] = src[i];
  }

  // Копируем вставляемую строку
  for (size_t i = 0; i < str_len; i++) {
    result[start_index + i] = str[i];
  }

  // Копируем оставшуюся часть исходной строки после start_index
  for (size_t i = start_index; i < src_len; i++) {
    result[str_len + i] = src[i];
  }

  // Завершаем строку нулевым символом
  result[new_len] = '\0';

  return result;
}

// Проверка, является ли символ одним из символов для обрезки
bool is_trim_char(char c, const char *trim_chars) {
  while (*trim_chars != '\0') {
    if (c == *trim_chars) {
      return true;
    }
    trim_chars++;
  }
  return false;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) {
    return NULL;
  }

  // Определяем длину исходной строки
  size_t src_len = 0;
  while (src[src_len] != '\0') {
    src_len++;
  }

  // Определяем начало обрезанной строки
  const char *start = src;
  while (*start != '\0' && is_trim_char(*start, trim_chars)) {
    start++;
  }

  // Определяем конец обрезанной строки
  const char *end = src + src_len - 1;
  while (end >= start && is_trim_char(*end, trim_chars)) {
    end--;
  }

  // Вычисляем длину новой строки
  size_t new_len = end >= start ? (end - start + 1) : 0;

  // Выделяем память для новой строки
  char *result = (char *)malloc((new_len + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;  // Обработка ошибки выделения памяти
  }

  // Копируем обрезанную часть строки
  for (size_t i = 0; i < new_len; i++) {
    result[i] = start[i];
  }

  // Завершаем строку нулевым символом
  result[new_len] = '\0';

  return result;
}

void *s21_to_upper(const char *str) {
  if (str == NULL) {
    return NULL;
  }

  // Определяем длину входной строки
  size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }

  // Выделяем память под новую строку
  char *result = (char *)malloc((length + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;  // Обработка ошибки выделения памяти
  }

  // Преобразуем каждый символ в верхний регистр
  for (size_t i = 0; i < length; i++) {
    result[i] = toupper((unsigned char)str[i]);
  }
  result[length] = '\0';  // Завершаем строку нулевым символом

  return result;
}

void *s21_to_lower(const char *str) {
  if (str == NULL) {
    return NULL;
  }

  // Определяем длину входной строки
  size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }

  // Выделяем память под новую строку
  char *result = (char *)malloc((length + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;  // Обработка ошибки выделения памяти
  }

  // Преобразуем каждый символ в нижний регистр
  for (size_t i = 0; i < length; i++) {
    result[i] = tolower((unsigned char)str[i]);
  }
  result[length] = '\0';  // Завершаем строку нулевым символом

  return result;
}
