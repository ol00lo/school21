#include <math.h>
#include <stdio.h>

void print_anezi(double x) { printf("%.7lf", 1.0 / (1.0 + x * x)); }

void print_bernulli(double x) {
    double s1 = sqrt(1.0 + 4.0 * x * x);
    double s2 = s1 - x * x - 1;
    if (s2 < 0) {
        printf("-");
        return;
    }
    printf("%.7lf", sqrt(s2));
}

void print_hyperbola(double x) {
    if (x == 0) {
        printf("-");
        return;
    }
    printf("%.7lf", 1 / x / x);
}

int main() {
    const double PI = 3.14159265358979323846;
    const int N_points = 42;
    const double len = 2 * PI / (N_points - 1);

    for (int i = 0; i < N_points; i++) {
        double curr_point = -PI + i * len;

        printf("%.7lf | ", curr_point);
        print_anezi(curr_point);
        printf(" | ");
        print_bernulli(curr_point);
        printf(" | ");
        print_hyperbola(curr_point);
        if (i != N_points - 1) printf("\n");
    }

    return 0;
}