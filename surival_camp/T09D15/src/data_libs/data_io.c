#include "data_io.h"

int input(double **data, int *n) {
    if (scanf("%d", n) != 1 || *n <= 0) return 1;
    *data = malloc(*n * sizeof(double));
    for (int i = 0; i < *n; i++)
        if (scanf("%lf", *data + i) != 1) return 1;
    return 0;
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2lf", data[i]);
        if (i < n - 1) printf(" ");
    }
}