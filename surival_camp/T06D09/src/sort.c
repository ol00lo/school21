#include <stdio.h>
#define N 10

int input(int *a);
void sort(int *a);
void output(int *a);

int main() {
    int data[N];
    if (input(data)) {
        printf("n/a");
        return 1;
    }
    sort(data);
    output(data);
    return 0;
}

int input(int *a) {
    for (int *p = a; p - a < N; p++) {
        if (scanf("%d", p) != 1) return 1;
    }
    return 0;
}

void sort(int *a) {
    for (int *j = a; j - a < N; j++) {
        for (int *i = a; i - a < N - 1 - (j - a); i++) {
            if (*i > *(i + 1)) {
                int tmp = *i;
                *i = *(i + 1);
                *(i + 1) = tmp;
            }
        }
    }
}

void output(int *a) {
    for (int *p = a; p - a < N; p++) {
        printf("%d", *p);
        if (p - a < N - 1) printf(" ");
    }
}