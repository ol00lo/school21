#include <stdio.h>
#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

int main() {
    int data[NMAX];
    int N;
    if (input(data, &N)) {
        printf("n/a");
        return 1;
    }
    int res = sum_numbers(data, N);
    if (res == 0) {
        printf("n/a");
        return 1;
    }

    int out[NMAX];

    printf("%d\n", res);
    int n = find_numbers(data, N, res, out);
    output(out, n);
}

int input(int *buffer, int *length) {
    if (scanf("%d", length) != 1 || *length > NMAX || *length <= 0) return 1;
    for (int *p = buffer; p - buffer < *length; p++) {
        if (scanf("%d", p) != 1) return 1;
    }
    return 0;
}

void output(int *buffer, int length) {
    for (int *p = buffer; p - buffer < length; p++) {
        printf("%d", *p);
        if (p - buffer < length - 1) printf(" ");
    }
}

int sum_numbers(int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0 && buffer[i] != 0) {
            sum += buffer[i];
        }
    }
    return sum;
}

int find_numbers(int *buffer, int length, int number, int *numbers) {
    int n = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] == 0) continue;
        if (number % buffer[i] == 0) {
            numbers[n] = buffer[i];
            n++;
        }
    }
    return n;
}
