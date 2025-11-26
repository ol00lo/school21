#include <stdio.h>
#define NMAX 10

int input(int *a, int *n, int *c);
void shift(int *a, int n, int c);
void output(int *a, int n);

int main() {
    int A[NMAX];
    int n, c;
    if (input(A, &n, &c)) {
        printf("n/a");
        return 1;
    }

    shift(A, n, c);
    output(A, n);
}

int input(int *a, int *n, int *c) {
    if (scanf("%d", n) != 1 || *n > NMAX || *n <= 0) return 1;
    for (int *p = a; p - a < *n; p++)
        if (scanf("%d", p) != 1) return 1;
    if (scanf("%d", c) != 1) return 1;
    return 0;
}

void left_shift(int *a, int n, int c) {
    for (int i = 0; i < c; i++) {
        int tmp = a[0];
        for (int j = 0; j < n - 1; j++) a[j] = a[j + 1];

        a[n - 1] = tmp;
    }
}

void right_shift(int *a, int n, int c) {
    for (int i = 0; i < c; i++) {
        int tmp = a[n - 1];
        for (int j = n - 1; j > 0; j--) a[j] = a[j - 1];

        a[0] = tmp;
    }
}

void shift(int *a, int n, int c) {
    c = c % n;
    if (c < 0)
        right_shift(a, n, -c);
    else if (c > 0)
        left_shift(a, n, c);
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d", *p);
        if (p - a < n - 1) printf(" ");
    }
}