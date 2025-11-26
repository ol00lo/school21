#include <stdio.h>

int is_prime(int a) {
    if (a == 1 || a == 2) return 1;
    int i = 1;
    while (i * i <= a) {
        i++;
        int j = 0;
        while (i * j < a) {
            j++;
        }
        if (i * j == a) {
            return 0;
        }
    }
    return 1;
}

int find_nod(int a) {
    if (a < 0) a = -a;
    if (a == 0) return -1;
    if (a == 1) return 1;

    int nod = -1;
    for (int i = 2; i < a; i++) {
        int j = 1;
        while (i * j < a) {
            j++;
        }
        if (i * j == a && is_prime(i)) {
            nod = i;
        }
    }
    return nod;
}

int main() {
    int a;
    if (scanf("%d", &a) != 1) {
        printf("n/a");
        return 1;
    }
    printf("%d", find_nod(a));
    return 0;
}