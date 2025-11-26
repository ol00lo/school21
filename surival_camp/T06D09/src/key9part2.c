#include <stdio.h>
#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

int input(int *a);
void output(int *a, int n);

int main() {
    int n1[LEN];
    int len1 = input(n1);

    int n2[LEN];
    int len2 = input(n2);

    int sum_buff[LEN];
    int sub_buff[LEN];
    int sum_len = 0, sub_len = 0;

    sum(n1, len1, n2, len2, sum_buff, &sum_len);
    sub(n1, len1, n2, len2, sub_buff, &sub_len);

    output(sum_buff, sum_len);
    printf("\n");
    output(sub_buff, sub_len);

    return 0;
}

int input(int *a) {
    int i = 0;
    int num;
    while (scanf("%d", &num) == 1) {
        a[i] = num;
        i++;
        char c;
        if (scanf("%c", &c) != 1) break;
        if (c == '\n') break;
    }
    return i;
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int c = 0;
    int i = len1 - 1, j = len2 - 1, k = 0;

    while (i >= 0 || j >= 0 || c) {
        int n1 = 0;
        int n2 = 0;
        if (i >= 0) n1 = buff1[i--];
        if (j >= 0) n2 = buff2[j--];
        int sum = n1 + n2 + c;

        result[k] = sum % 10;
        k++;
        c = sum / 10;
    }

    *result_length = k;
    for (int i = 0; i < k / 2; i++) {
        int tmp = result[i];
        result[i] = result[k - 1 - i];
        result[k - 1 - i] = tmp;
    }
}

int compn(int *buff1, int len1, int *buff2, int len2) {
    if (len1 != len2) return len1 - len2;
    for (int i = 0; i < len1; i++)
        if (buff1[i] != buff2[1]) return buff1[i] - buff2[i];

    return 0;
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    if (compn(buff1, len1, buff2, len2) < 0) return;

    int c = 0;
    int i = len1 - 1, j = len2 - 1, k = 0;

    while (i >= 0) {
        int n1 = buff1[i--];
        int n2 = 0;
        if (j >= 0) n2 = buff2[j--];

        if (n1 < n2 + c) {
            result[k] = n1 + 10 - n2 - c;
            k++;
            c = 1;
        } else {
            result[k] = n1 - n2 - c;
            k++;
            c = 0;
        }
    }
    *result_length = k;
    while (*result_length > 1 && result[*result_length - 1] == 0) (*result_length)--;

    for (int i = 0; i < *result_length / 2; i++) {
        int tmp = result[i];
        result[i] = result[*result_length - 1 - i];
        result[*result_length - 1 - i] = tmp;
    }
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d", *p);
    }
}
