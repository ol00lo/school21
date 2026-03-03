#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  void* result = S21_NULL;
  const unsigned char* pointer = (unsigned char*)str;
  const unsigned char new_c = (unsigned char)c;

  for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
    if (pointer[i] == new_c) result = (void*)(pointer + i);
  }
  return result;
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  const unsigned char* s1 = (unsigned char*)str1;
  const unsigned char* s2 = (unsigned char*)str2;
  s21_size_t index = 0;

  for (; index < n && (s1[index] == s2[index]); index++);
  return (n == 0) || (n == index) ? 0 : (int)(s1[index] - s2[index]);
}

char* s21_strchr(const char* str, int c) {
  if (str == S21_NULL) return S21_NULL;

  while (*str && *str != c) str++;
  return (*str == c) ? (char*)str : S21_NULL;
}

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t i = 0;

  while (str1[i] && !s21_strchr(str2, str1[i])) i++;
  return i;
}

char* s21_strerror(int errnum) {
  const char* message;

  if (errnum < 1 || errnum > 107) {
    message = "Unknown error";
  } else {
    const char* errors[] = ERRORS_LIST;
    message = errors[errnum];
  }
  return (char*)message;
}

char* s21_strpbrk(const char* str1, const char* str2) {
  char* flag = S21_NULL;

  while (*str1 && !(flag = s21_strchr(str2, *str1))) str1++;
  return flag ? (char*)str1 : S21_NULL;
}

char* s21_strtok(char* str, const char* delim) {
  static char* new_str = S21_NULL;
  char* token = S21_NULL;

  if (str != S21_NULL) {
    new_str = str;
  }
  if (new_str != S21_NULL) {
    while (*new_str && s21_strchr(delim, *new_str)) new_str++;
    if (*new_str != '\0') token = new_str;

    while (*new_str && !s21_strchr(delim, *new_str)) new_str++;
    if (*new_str != '\0') *(new_str++) = '\0';
  }
  return token;
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  char* dest_c = (char*)dest;
  const char* src_c = (const char*)src;
  for (s21_size_t i = 0; i < n; i++) {
    dest_c[i] = src_c[i];
  }
  return dest;
}

s21_size_t s21_strlen(const char* str) {
  s21_size_t lenght = 0;
  while (str[lenght] != '\0') {
    lenght++;
  }
  return lenght;
}

char* s21_strrchr(const char* str, int c) {
  int i = 0;
  char* res = S21_NULL;
  while (str[i] != '\0') {
    if (str[i] == c) res = (char*)&str[i];
    i++;
  }
  return res;
}

char* s21_strstr(const char* haystack, const char* needle) {
  int i = 0;
  int error = 1;
  char* res = S21_NULL;
  while (haystack[i] != '\0') {
    int j = 0, start = i;
    while (haystack[start] == needle[j] && needle[j] != '\0') {
      start++;
      j++;
    }
    if (needle[j] == '\0') {
      error = 0;
      break;
    }
    i++;
  }
  if (!error) {
    res = (char*)&haystack[i];
  }
  return res;
}

void* s21_to_upper(const char* str) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  char* str1 = S21_NULL;
  if (len != 0) {
    str1 = malloc((len + 1) * sizeof(char));
  }
  if (str1 != S21_NULL) {
    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        str1[i] = str[i] - ('a' - 'A');
      } else {
        str1[i] = str[i];
      }
    }
    str1[len] = '\0';
  }
  return str1;
}

void* s21_to_lower(const char* str) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  char* str1 = S21_NULL;
  if (len != 0) {
    str1 = malloc((len + 1) * sizeof(char));
  }
  if (str1 != S21_NULL) {
    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        str1[i] = str[i] + ('a' - 'A');
      } else {
        str1[i] = str[i];
      }
    }
    str1[len] = '\0';
  }
  return str1;
}

void* s21_memset(void* str, int c, s21_size_t n) {
  unsigned char* ptr = (unsigned char*)str;
  unsigned char byte = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = byte;
  }
  return str;
}

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  while (i < n) {
    dest[i] = '\0';
    i++;
  }
  return dest;
}

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) return S21_NULL;
  if (start_index > s21_strlen(src)) return S21_NULL;

  s21_size_t str_len = s21_strlen(str);
  s21_size_t src_len = s21_strlen(src);
  s21_size_t total_len = str_len + src_len;

  char* result = malloc(sizeof(char) * total_len + 1);

  if (result == S21_NULL)
    result = S21_NULL;
  else {
    s21_size_t i = 0;

    for (s21_size_t j = 0; j < start_index; j++, i++) {
      result[i] = src[j];
    }

    for (s21_size_t j = 0; j < str_len; j++, i++) {
      result[i] = str[j];
    }

    for (s21_size_t j = start_index; src[j] != '\0'; j++, i++) {
      result[i] = src[j];
    }
    result[i] = '\0';
  }

  return result;
}

void* s21_trim(const char* src, const char* trim_chars) {
  if (src == S21_NULL) return S21_NULL;
  if (trim_chars == S21_NULL) trim_chars = " \t\n\v\f\r";
  char* result = S21_NULL;

  if (src[0] == '\0') {
    result = malloc(sizeof(char) * 1);
    if (result != S21_NULL) {
      result[0] = '\0';
    }
  } else {
    int len = s21_strlen(src);
    int start = 0;
    while (start < len && s21_strchr(trim_chars, src[start]) != S21_NULL) {
      start++;
    }

    if (start == len) {
      result = malloc(sizeof(char));
      if (result != S21_NULL) {
        result[0] = '\0';
      }
    } else {
      int end = len - 1;
      while (end >= start && s21_strchr(trim_chars, src[end]) != S21_NULL) {
        end--;
      }

      int new_len = end - start + 1;
      result = malloc(sizeof(char) * (new_len + 1));

      if (result != S21_NULL) {
        for (int i = 0; i < new_len; i++) {
          result[i] = src[start + i];
        }
        result[new_len] = '\0';
      }
    }
  }
  return result;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  size_t counter = 0;
  int res = 0;
  int stop = 0;
  while (counter < n && !stop) {
    unsigned char char1 = (unsigned char)str1[counter];
    unsigned char char2 = (unsigned char)str2[counter];
    if (char1 != char2) {
      res = char1 - char2;
      stop = 1;
    } else if (char1 == '\0')
      stop = 1;
    counter++;
  }
  return res;
}

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  char* p = dest;
  while (*p != '\0') {
    p++;
  }
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    *p = src[i];
    p++;
    i++;
  }
  *p = '\0';
  return dest;
}