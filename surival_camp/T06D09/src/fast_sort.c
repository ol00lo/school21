#include <stdio.h>
#define N 10

int input(int *a);
void fast_sort(int *a, int left, int right);
void pyramid_sort(int *a);
void output(int *a);
void copy(int *a, int *b);

int main() {
    int data1[N];
    int data2[N];
    if (input(data1)) {
        printf("n/a");
        return 1;
    }
    copy(data1, data2);

    fast_sort(data1, 0, N - 1);
    output(data1);

    printf("\n");

    pyramid_sort(data2);
    output(data2);
    return 0;
}

int input(int *a) {
    for (int *p = a; p - a < N; p++) {
        if (scanf("%d", p) != 1) return 1;
    }
    return 0;
}

void copy(int *a, int *b) {
    for (int i = 0; i < N; i++) {
        b[i] = a[i];
    }
}

void fast_sort(int *a, int left, int right) {
    if (left < right) {
        int piv = a[(left + right) / 2];
        int i = left;
        int j = right;
        while (i <= j) {
            while (a[i] < piv) i++;
            while (a[j] > piv) j--;
            if (i <= j) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
                i++;
                j--;
            }
            fast_sort(a, left, j);
            fast_sort(a, i, right);
        }
    }
}

void help_sort(int *a, int n, int i) {
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[max]) max = l;
    if (r < n && a[r] > a[max]) max = r;
    if (max != i) {
        int tmp = a[i];
        a[i] = a[max];
        a[max] = tmp;
        help_sort(a, n, max);
    }
}

void pyramid_sort(int *a) {
    for (int i = N / 2 - 1; i >= 0; i--) help_sort(a, N, i);

    for (int i = N - 1; i >= 0; i--) {
        int tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        help_sort(a, i, 0);
    }
}

void output(int *a) {
    for (int *p = a; p - a < N; p++) {
        printf("%d", *p);
        if (p - a < N - 1) printf(" ");
    }
}