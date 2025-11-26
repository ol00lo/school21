#include "s21_string.h"

void s21_str_len_test(void);
void s21_strcmp_test(void);
void s21_strcpy_test(void);
void s21_strcat_test(void);
void s21_strchr_test(void);
void s21_strstr_test(void);

int main(void) {
#ifdef STRLEN
    s21_str_len_test();
#elif defined STRCMP
    s21_strcmp_test();
#elif defined STRCPY
    s21_strcpy_test();
#elif defined STRCAT
    s21_strcat_test();
#elif defined STRCHR
    s21_strchr_test();
#elif defined STRSTR
    s21_strstr_test();
#endif
    return 0;
}

void s21_str_len_test(void) {
    char *strings[] = {"I am blinding", "autoluminescent", "I am white heat", "", " ", "\n"};
    size_t expect_lens[] = {13, 15, 15, 0, 1, 1};
    for (size_t i = 0; i < sizeof(expect_lens) / sizeof(size_t); i++) {
        char *cur_str = strings[i];
        size_t cur_res = s21_strlen(cur_str);
        printf("%s %zu %s\n", cur_str, cur_res, (cur_res == expect_lens[i] ? "SUCCESS" : "FAIL"));
    }
}

void s21_strcmp_test(void) {
    char *strings1[] = {"I am blinding", "autoluminescent", "I am white heat", "", " ", "\n"};
    char *strings2[] = {"I'm blinding", "autolluminescent", "I am white heat", "", " ", "\n"};
    int expect[] = {-1, 1, 0, 0, 0, 0};
    for (size_t i = 0; i < sizeof(expect) / sizeof(int); i++) {
        char *str1 = strings1[i];
        char *str2 = strings2[i];
        int cur_res = s21_strcmp(str1, str2);
        printf("%s %s %d %s\n", str1, str2, cur_res, (cur_res == expect[i] ? "SUCCESS" : "FAIL"));
    }
}

void s21_strcpy_test(void) {
    char dest[20];
    char *strings[] = {"I'm blinding", "autolluminescent", "I am white heat", "", " ", "\n"};
    for (size_t i = 0; i < sizeof(strings) / sizeof(char *); i++) {
        char *str = strings[i];
        s21_strcpy(dest, str);
        int res = s21_strcmp(dest, str);
        printf("%s %s %s\n", str, dest, (res == 0 ? "SUCCESS" : "FAIL"));
    }
}

void s21_strcat_test(void) {
    char *strings1[] = {"I'm ", "autol", "I a", "", " ", "\n"};
    char *strings2[] = {"blinding", "uminescent", "m white heat", "", "   ", "\n"};

    char *expect[] = {"I'm blinding", "autoluminescent", "I am white heat", "", "    ", "\n\n"};
    for (size_t i = 0; i < sizeof(expect) / sizeof(char *); i++) {
        char str1[20];
        char str2[20];
        s21_strcpy(str1, strings1[i]);
        s21_strcpy(str2, strings2[i]);
        printf("%s %s ", str1, str2);
        s21_strcat(str1, str2);

        printf("%s %s\n", str1, (s21_strcmp(str1, expect[i]) == 0 ? "SUCCESS" : "FAIL"));
    }
}

void s21_strchr_test(void) {
    char *strings[] = {"I am blinding", "autoluminescent", "I am white heat", "", " ", "\n"};
    char n[] = {'b', ' ', 'i', 'a', ' ', '\n'};
    char *expect[] = {strings[0] + 5, NULL, strings[2] + 7, NULL, strings[4], strings[5]};

    for (size_t i = 0; i < sizeof(expect) / sizeof(char *); i++) {
        char *str = strings[i];
        char *res = s21_strchr(str, n[i]);
        printf("%s %c %s %s\n", str, n[i], res, (res == expect[i] ? "SUCCESS" : "FAIL"));
    }
}

void s21_strstr_test(void) {
    char *strings1[] = {"I am blinding", "autoluminescent", "I am white heat", "", " ", "\n"};
    char *strings2[] = {"am", "cen", "'am", "", " ", "\n"};
    char *expect[] = {strings1[0] + 2, strings1[1] + 11, NULL, strings1[3], strings1[4], strings1[5]};
    for (size_t i = 0; i < sizeof(strings2) / sizeof(strings2[0]); i++) {
        char *str1 = strings1[i];
        char *str2 = strings2[i];
        char *res = s21_strstr(str1, str2);

        printf("%s %s %s %s\n", str1, str2, res ? res : "NULL", (res == expect[i] ? "SUCCESS" : "FAIL"));
    }
}