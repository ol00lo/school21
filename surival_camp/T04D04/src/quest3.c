#include <stdio.h>

int n_fib(int n) {
    if (n == 1 || n == 2) return 1;
    return n_fib(n - 1) + n_fib(n - 2);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }
    if (n <= 0) {
        printf("n/a");
        return 1;
    }
    printf("%d", n_fib(n));
    return 0;
}