#include "s21_string.h"

size_t s21_strlen(const char *str) {
    size_t len = 0;
    while (*str) {
        len++;
        str++;
    }
    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && (*str1 - *str2) == 0) {
        str1++;
        str2++;
    }
    return (*str1 - *str2 == 0) ? 0 : (*str1 - *str2) / abs(*str1 - *str2);
}

char *s21_strcpy(char *restrict str1, const char *restrict str2) {
    char *ptr1 = str1;
    while (*str2) {
        *ptr1 = *str2;
        ptr1++;
        str2++;
    }
    *ptr1 = *str2;
    return str1;
}

char *s21_strcat(char *restrict str1, const char *restrict str2) {
    char *ptr1 = str1;
    while (*ptr1) {
        ptr1++;
    }
    while (*str2) {
        *ptr1 = *str2;
        ptr1++;
        str2++;
    }
    *ptr1 = *str2;
    return str1;
}

char *s21_strchr(const char *str, int n) {
    while (*str && *str != n) {
        str++;
    }
    char *ptr = NULL;
    if (*str != 0) {
        ptr = (char *)str;
    }
    return ptr;
}

char *s21_strstr(const char *str1, const char *str2) {
    if (*str2 == '\0') return (char *)str1;
    for (size_t i = 0; str1[i] != '\0'; i++) {
        size_t j = 0;
        while (str2[j] != '\0' && str1[i + j] == str2[j]) {
            j++;
        }
        if (str2[j] == '\0') {
            return (char *)(str1 + i);
        }
    }
    
    return NULL;
}

