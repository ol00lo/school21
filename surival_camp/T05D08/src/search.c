#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
int search(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        printf("n/a");
        return 1;
    }
    printf("%d", search(data, n));
    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) return 1;
    if (*n <= 0 || *n > NMAX) return 1;
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) return 1;
    }
    return 0;
}

double mean(int *a, int n) {
    int sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    return (double)sum / n;
}

double variance(int *a, int n) {
    double m = mean(a, n);
    double s = 0;
    for (int *p = a; p - a < n; p++) {
        s += (*p - m) * (*p - m);
    }
    return s / n;
}

int search(int *a, int n) {
    double m = mean(a, n);
    double sv = sqrt(variance(a, n));

    for (int *p = a; p - a < n; p++) {
        if (*p % 2 != 0)
            continue;
        else if (*p < m)
            continue;
        else if (*p > m + 3 * sv)
            continue;
        else if (*p == 0)
            continue;
        else
            return *p;
    }
    return 0;
}